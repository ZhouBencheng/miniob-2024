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

UpdateStmt::UpdateStmt(Table *table, Field *field, std::unique_ptr<Expression> expr, int value_amount, FilterStmt* filter)
    : table_(table), field_(field), expr_(std::move(expr)),  filter_(filter), value_amount_(value_amount)
{}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update, Stmt *&stmt)
{
  // 检查表名称和属性名称是否为非空
  const char *table_name = update.relation_name.c_str();
  const char *attribute_name = update.attribute_name.c_str();
  if (table_name == nullptr || attribute_name == nullptr || db == nullptr) {
    LOG_WARN("invalid argument. table_name=%p, attribute_name=%p", table_name, attribute_name);
    return RC::INVALID_ARGUMENT;
  }

  // 检查表是否存在
  Table *table = db->find_table(table_name);
  if (table == nullptr) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // 检查属性是否存在
  Field *field = table->find_field(attribute_name);
  if (field == nullptr) {
    LOG_WARN("no such field. table_name=%s, field_name=%s", table_name, attribute_name);
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table*>(std::string(table_name), table));

  // 构造ExpressionBinder对象
  BinderContext binder_context;
  binder_context.add_table(table);
  ExpressionBinder expression_binder(binder_context, db);
  expression_binder.set_default_table(table);

  if (update.expr->type() == ExprType::SUBQUERY) {
    static_cast<SubQueryExpr *>(update.expr.get())->generate_select_stmt(db, binder_context);
  }

  // FilterStmt::create函数：当condition中不存在过滤条件时，依然将filter_stmt指针构造为一个空的FilterStmt对象
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
    db,                                         // 数据库指针
    table,                                      // 默认表指针
    &table_map,                                 // 映射表指针
    expression_binder,                          // 表达式绑定器
    update.conditions.data(),                   // 过滤条件数组指针
    static_cast<int>(update.conditions.size()), // 过滤条件个数
    filter_stmt                                 // (out)输出的FilterStmt指针
  );
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  stmt = new UpdateStmt(table, field, std::move(update.expr), /* update仅对一个属性更新 */1, filter_stmt);

  return RC::SUCCESS;
}
