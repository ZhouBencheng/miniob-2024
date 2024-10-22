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
// Created by Wangyunlai on 2022/12/29.
//

#include "sql/optimizer/predicate_rewrite.h"
#include "sql/operator/logical_operator.h"

// 用于对谓词算子的父节点使用的重写规则
RC PredicateRewriteRule::rewrite(std::unique_ptr<LogicalOperator> &oper, bool &change_made)
{
  std::vector<std::unique_ptr<LogicalOperator>> &child_opers = oper->children(); // 谓词重写规则只对拥有一个子节点的逻辑算子进行重写
  if (child_opers.size() != 1) {
    return RC::SUCCESS;
  }

  auto &child_oper = child_opers.front();
  if (child_oper->type() != LogicalOperatorType::PREDICATE) {
    return RC::SUCCESS;
  }

  std::vector<std::unique_ptr<Expression>> &expressions = child_oper->expressions();
  if (expressions.size() != 1) {
    return RC::SUCCESS;
  }

  // 在logical_plan_generator中根据filter_stmt生成predicate算子过程中，一般最后用一个ConjunciotnExpr连接所有ComparisonExpr
  // 并使用这个ConjunctionExpr构造谓词算子
  // 而这里针对的情况是当where语句中的谓词不是一个不等式，而是一个确定的value，例如where 1，条件始终为真并且构造出ValueExpr 
  std::unique_ptr<Expression> &expr = expressions.front();
  if (expr->type() != ExprType::VALUE) {
    return RC::SUCCESS;
  }

  // 如果仅有的一个子节点是predicate
  // 并且这个子节点可以判断为恒为TRUE，那么可以省略这个子节点，并把他的子节点们（就是孙子节点）接管过来
  // 如果可以判断恒为false，那么就可以删除子节点
  auto value_expr = static_cast<ValueExpr *>(expr.get());
  bool bool_value = value_expr->get_value().get_boolean();
  if (true == bool_value) {
    std::vector<std::unique_ptr<LogicalOperator>> grand_child_opers;
    grand_child_opers.swap(child_oper->children());
    child_opers.clear();
    for (auto &grand_child_oper : grand_child_opers) {
      oper->add_child(std::move(grand_child_oper));
    }
  } else {
    child_opers.clear();
  }

  change_made = true;
  return RC::SUCCESS;
}
