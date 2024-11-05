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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include <common/log/log.h>
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <sql/parser/expression_binder.h>
#include "sql/expr/expression.h"

UpdateStmt::UpdateStmt(Table *table, std::vector<std::pair<Field *, std::unique_ptr<Expression>>> assignments, FilterStmt* filter)
    : table_(table), assignments_(std::move(assignments)), filter_(filter)
{}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  // 检查表名称和属性名称是否为非空
  const char *table_name = update.relation_name.c_str();

  // 检查表是否存在
  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table*>(std::string(table_name), table));

  // 构造ExpressionBinder对象
  BinderContext binder_context;
  binder_context.add_table(table);
  ExpressionBinder expression_binder(binder_context, db);
  expression_binder.set_default_table(table);

  // 检查赋值列表中的属性和表达式是否合法存在
  std::vector<std::pair<Field *, std::unique_ptr<Expression>>> assignments;
  for (auto &assignment : update.assignments) {
    // 处理一个赋值语句中的属性合法性
    const char *attribute_name = assignment.first.c_str();
    if (attribute_name == nullptr) {
      LOG_WARN("invalid argument: attribute_name is null");
      return RC::INVALID_ARGUMENT;
    }

    Field *field = table->find_field(attribute_name);
    if (field == nullptr) {
      LOG_WARN("no such field. table_name=%s, field_name=%s", table_name, attribute_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    // 处理一个赋值语句中的表达式合法性
    if (assignment.second->type() == ExprType::SUBQUERY) {
      RC rc = static_cast<SubQueryExpr *>(assignment.second.get())->generate_select_stmt(db, binder_context);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to generate sub query select stmt in update stmt. rc=%d:%s", rc, strrc(rc));
        return rc;
      }
    }

    assignments.emplace_back(std::make_pair(field, std::move(assignment.second)));
  }

  // FilterStmt::create函数：当condition中不存在过滤条件时，依然将filter_stmt指针构造为一个空的FilterStmt对象
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
    db,                                         // 数据库指针
    expression_binder,                          // 表达式绑定器
    update.conditions.data(),                   // 过滤条件数组指针
    static_cast<int>(update.conditions.size()), // 过滤条件个数
    filter_stmt                                 // (out)输出的FilterStmt指针
  );
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, std::move(assignments), filter_stmt);

  return RC::SUCCESS;
}
