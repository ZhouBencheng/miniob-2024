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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <sql/parser/expression_binder.h>

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

// 将where条件子句中的每一个过滤条件转化为FilterUnit对象，并封装在vector容器中，默认所有条件之间是AND关系
RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    ExpressionBinder &expression_binder, ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;

    // 注意在将ConditionSqlNode类型的成员变量都转化为Expression的unique指针时，我们从parser到resolver传递都需要使用移动语义
    // 因此在下面这个方法中，我们将conditions中的元素一个个构造为FilterUnit对象后，conditions中的元素也将不复存在
    rc = create_filter_unit(db, default_table, tables, expression_binder, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

/**
 * @brief 当过滤条件中操作对象是属性是才调用该函数，根据该属性获取相应的Table指针和FieldMeta指针
 * @param db              指向Db数据库类型的指针
 * @param default_table   默认表指向FROM子句中唯一存在的表，当FROM中有多个表，默认表空指针；当where子句中属性没有指定关系名时，使用默认表
 * @param tables          表名到表指针的映射表，存放FROM子句钟中存在的表
 * @param attr            囊括属性名和关系名的结构体
 * @param table           (out)指向Table表类型的指针
 * @param field           (out)指向FieldMeta字段类型的指针
 */
RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    ExpressionBinder &expression_binder, ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;

  vector<unique_ptr<Expression>> bound_expressions;
  RC rc1 = expression_binder.bind_expression(condition.left_expression, bound_expressions);
  RC rc2 = expression_binder.bind_expression(condition.right_expression, bound_expressions);
  if (rc1 != RC::SUCCESS || rc2 != RC::SUCCESS) {
    LOG_WARN("failed to bind expression when creating filter stmt");
    return rc1 != RC::SUCCESS ? rc1 : rc2;
  }
  filter_unit->set_left(std::move(bound_expressions[0]));
  filter_unit->set_right(std::move(bound_expressions[1]));

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}
