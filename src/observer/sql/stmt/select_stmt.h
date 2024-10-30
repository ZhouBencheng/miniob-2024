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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <memory>
#include <vector>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "sql/parser/expression_binder.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  /**
   * @brief 表示一个join语句，存储ParseSqlNode中的一个InnerJoinSqlNode
   * @ingroup Statement
   */
  class JoinTable { // 一个JoinTables对象对应一个InnerJoinSqlNode节点的解析结果
  public:
    JoinTable() = default;
    ~JoinTable() = default;
    JoinTable(JoinTable &&other) { // 移动构造
      join_tables_.swap(other.join_tables_);
      on_conds_.swap(other.on_conds_);
    }
    void push_join_table(Table *table, FilterStmt *on_cond) { // 完善一个Inner Join的解析结果
      join_tables_.emplace_back(table);
      on_conds_.emplace_back(on_cond);
    }
    const std::vector<Table *>      &join_tables() const { return join_tables_; }
    const std::vector<FilterStmt *> &on_conds() const { return on_conds_; }
  private:
    std::vector<Table *>      join_tables_;
    std::vector<FilterStmt *> on_conds_;
  };

public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt, const BinderContext &parent_binder_context = BinderContext()); // 默认构造为空BinderContext

public:
  const std::vector<JoinTable> &join_tables() const { return join_tables_; }
  FilterStmt                    *filter_stmt() const { return filter_stmt_; }

  std::vector<std::unique_ptr<Expression>> &query_expressions() { return query_expressions_; }
  std::vector<std::unique_ptr<Expression>> &group_by() { return group_by_; }

private:
  /**
   * @brief 处理from子句
   * @ingroup Statement
   * @details 处理from子句中vector<InnerJoinSqlNode>，将解析出的内连接关系转换为JoinTables对象
   * @param db               数据库指针
   * @param inner_join_nodes parser解析出的内连接关系
   * @param binder_context   (out)绑定上下文
   * @param tables           (out)表指针数组
   * @param table_map        (out)表名和表指针的映射
   * @param join_tables      (out)存储JoinTables对象的数组
   */
  static RC handle_from_clause(Db            *db, 
    std::vector<InnerJoinSqlNode>            &inner_join_nodes,
    BinderContext                            &binder_context, 
    std::vector<Table *>                     &tables, 
    std::unordered_map<std::string, Table *> &table_map,
    std::vector<JoinTable>                  &join_tables);

private:
  std::vector<std::unique_ptr<Expression>> query_expressions_;
  std::vector<JoinTable>                   join_tables_; // JoinTables类型数组存储外连接关系
  FilterStmt                              *filter_stmt_ = nullptr;
  std::vector<std::unique_ptr<Expression>> group_by_;
};
