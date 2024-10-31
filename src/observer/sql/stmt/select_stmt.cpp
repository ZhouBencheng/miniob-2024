/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC SelectStmt::handle_from_clause(Db       *db, 
  std::vector<InnerJoinSqlNode>            &inner_join_nodes,
  BinderContext                            &binder_context, 
  std::vector<Table *>                     &tables, 
  std::unordered_map<std::string, Table *> &table_map,
  std::vector<JoinTable>                  &join_tables)
{
  auto collect_and_check_table = [&](std::string &table_name) { // lamda表达式，用于解析一个表名到表指针
    const char *table_name_cstr = table_name.c_str();
    if (nullptr == table_name_cstr) {
      LOG_WARN("invalid argument. table name is null");
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name_cstr);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name_cstr);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    binder_context.add_table(table);
    tables.push_back(table);
    table_map.insert({table_name, table});
    return RC::SUCCESS;
  };

  /**
   * @brief 处理一个InnerJoinSqlNode中的一个表及其对应的on条件，并将解析出的表指针和on条件对应的FilterStmt对象存储到JoinTables对象中
   */
  auto handle_one_relation = [&](std::string &table_name, vector<ConditionSqlNode> &on_conds, JoinTable &jt) {
    RC rc = RC::SUCCESS;
    rc = collect_and_check_table(table_name);
    if (rc != RC::SUCCESS) { // 将当前表解析出表指针失败
      return rc;
    }

    FilterStmt      *filter_stmt = nullptr;
    ExpressionBinder expression_binder(binder_context, db);
    // 对于InnerJoinSqlNode中的basic_relation表，其on_conds为空，因此在JoinTables中只需要推入(Table *, nullptr)即可，FilterStmt对象为空
    if (!on_conds.empty()) {
      // 对于InnerJoinSqlNode中的join_relations表，其on_conds不为空，因此在JoinTables中需要推入(Table *, FilterStmt *)
      rc = FilterStmt::create(db, nullptr, &table_map, expression_binder, on_conds.data(), static_cast<int>(on_conds.size()), filter_stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot construct filter stmt");
        return rc;
      }
    }
    jt.push_join_table(table_map[table_name], filter_stmt);
    return RC::SUCCESS;
  };

  // 遍历外连接关系，处理每个InnerJoinSqlNode
  for (size_t i = 0; i < inner_join_nodes.size(); i++) {
    InnerJoinSqlNode &inner_join_node = inner_join_nodes[i];
    JoinTable jt;

    vector<ConditionSqlNode> on_conds;
    RC rc = handle_one_relation(inner_join_node.basic_relation, on_conds, jt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("handle basic relation failed. rc=%s", strrc(rc));
      return rc;
    }

    // 遍历内连接关系，处理每个join_relations表及其对应的on条件
    vector<std::string>                   &join_relations = inner_join_node.join_relations;
    vector<std::vector<ConditionSqlNode>> &conditions     = inner_join_node.conditions;
    for (size_t j = 0; j < join_relations.size(); j++) {
      rc = handle_one_relation(join_relations[j], conditions[j], jt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("handle join relation failed. rc=%s", strrc(rc));
        return rc;
      }
    }
    conditions.clear();

    join_tables.emplace_back(std::move(jt));
  }

  return RC::SUCCESS;
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, const BinderContext &parent_binder_context)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context = parent_binder_context; // 在子查询的解析中，获取父查询的表达式绑定背景

  // collect tables in `from` statement
  vector<Table *>                tables;
  unordered_map<string, Table *> table_map;
  vector<JoinTable>              join_tables;
  RC rc = handle_from_clause(db, select_sql.relations, binder_context, tables, table_map, join_tables);
  if (rc != RC::SUCCESS) {
    LOG_WARN("handle from clause failed. rc=%s", strrc(rc));
    return rc;
  }

  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder expression_binder(binder_context, db);
  
  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind select clause expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind group by clause expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  // 当FROM中不止一个表，则默认表不存在，默认表用于指定WHERE中未给出表名的属性的表
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
    expression_binder.set_default_table(default_table);
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  rc                      = FilterStmt::create(db,
      default_table,
      &table_map,
      expression_binder,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->join_tables_.swap(join_tables);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  stmt                      = select_stmt;
  return RC::SUCCESS;
}
