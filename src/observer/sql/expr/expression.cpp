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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/expr/arithmetic_operator.hpp"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "sql/parser/expression_binder.h"

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

bool FieldExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::FIELD) {
    return false;
  }
  const auto &other_field_expr = static_cast<const FieldExpr &>(other);
  return table_name() == other_field_expr.table_name() && field_name() == other_field_expr.field_name();
}

// TODO: 在进行表达式计算时，`chunk` 包含了所有列，因此可以通过 `field_id` 获取到对应列。
// 后续可以优化成在 `FieldExpr` 中存储 `chunk` 中某列的位置信息。
RC FieldExpr::get_column(Chunk &chunk, Column &column)
{
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    column.reference(chunk.column(field().meta()->field_id()));
  }
  return RC::SUCCESS;
}

RC FieldExpr::get_table_ptr(const Table **table_ptr) const
{
  *table_ptr = field_.table();
  return RC::SUCCESS;
}

bool ValueExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::VALUE) {
    return false;
  }
  const auto &other_value_expr = static_cast<const ValueExpr &>(other);
  return value_.compare(other_value_expr.get_value()) == 0;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

RC ValueExpr::get_column(Chunk &chunk, Column &column)
{
  column.init(value_);
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }
  rc = Value::cast_to(value, cast_type_, cast_value);
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &result) const
{
  Value value;
  RC rc = child_->get_value(tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

RC CastExpr::try_get_value(Value &result) const
{
  Value value;
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

RC CastExpr::traverse_check(const std::function<RC(Expression *)> &check_func)
{
  RC rc = RC::SUCCESS;
  rc = child_->traverse_check(check_func);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to traverse check child expression in cast expr. rc=%s", strrc(rc));
    return rc;
  }
  rc = check_func(this);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to check cast expr. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC  rc         = RC::SUCCESS;
  // null值和任何值比较都是返回false
  if ((left.attr_type() == AttrType::NULLS || right.attr_type() == AttrType::NULLS) &&
      (comp_ != IS_COMP && comp_ != IS_NOT_COMP)) {
    result = false;
    return rc;
  }
  result         = false;
  switch (comp_) {
    case EQUAL_TO: {
      int cmp_result = left.compare(right);
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      int cmp_result = left.compare(right);
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      int cmp_result = left.compare(right);
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      int cmp_result = left.compare(right);
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      int cmp_result = left.compare(right);
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      int cmp_result = left.compare(right);
      result = (cmp_result > 0);
    } break;
    case LIKE_COMP: {
      LOG_DEBUG("LIKE_COMP");
      result = left.like(right);
    } break;
    case NOT_LIKE_COMP: {
      LOG_DEBUG("NOT_LIKE_COMP");
      result = !left.like(right);
    } break;
    case IS_COMP: {
      result = (left.attr_type() == AttrType::NULLS && right.attr_type() == AttrType::NULLS);
    } break;
    case IS_NOT_COMP: {
      result = ((left.attr_type() != AttrType::NULLS && right.attr_type() == AttrType::NULLS) ||
                (left.attr_type() == AttrType::NULLS && right.attr_type() != AttrType::NULLS));
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *  left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr *  right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value left_value;
  Value right_value;
  RC rc = RC::SUCCESS;
  SubQueryExpr *left_subquery_expr = nullptr;
  SubQueryExpr *right_subquery_expr = nullptr;

  if (left_->type() == ExprType::SUBQUERY) {
    left_subquery_expr = static_cast<SubQueryExpr *>(left_.get());
    left_subquery_expr->open(nullptr);
  }
  if (right_->type() == ExprType::SUBQUERY) {
    right_subquery_expr = static_cast<SubQueryExpr *>(right_.get());
    right_subquery_expr->open(nullptr);
  }

  if (comp_ == EXISTS_COMP || comp_ == NOT_EXISTS_COMP) { // 在exists运算中，右表达式为空
    if (right_ != nullptr) {
      LOG_WARN("right expression should be null in EXISTS or NOT EXISTS comparison.");
      return RC::INVALID_ARGUMENT;
    }
    bool have_row = left_subquery_expr->have_row(&tuple);
    value.set_boolean(comp_ == EXISTS_COMP ? have_row : !have_row);
    return RC::SUCCESS;
  }

  left_->get_value(tuple, left_value); // 获取左表达式的值
  if (left_subquery_expr && left_subquery_expr->have_row(&tuple)) {
    LOG_WARN("left expression is a subquery but output multiple rows in comparison.");
    return RC::INVALID_ARGUMENT;
  }

  if (comp_ == IN_COMP || comp_ == NOT_IN_COMP) {
    if (left_value.attr_type() == AttrType::NULLS) { // 当左表达式为空时，无论如何当前in计算为false
      value.set_boolean(false);
      return RC::SUCCESS;
    }

    bool have_null = false;
    bool match     = false;
    while (RC::SUCCESS == (rc = right_->get_value(tuple, right_value))) {
      if (right_value.attr_type() == AttrType::NULLS) {
        have_null = true;
      } else if (left_value.compare(right_value) == 0) {
        match = true;
      }
    }
    value.set_boolean(comp_ == IN_COMP ? match : (have_null ? false : !match));
    return rc == RC::RECORD_EOF ? RC::SUCCESS : rc;
  }

  /* 以下部分为子查询以外普通表达式的比较计算 */
  rc = right_->get_value(tuple, right_value); // 非子查询运算中还没获取到右表达式的值
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression in comparison. rc=%s", strrc(rc));
    return rc;
  }
  if (right_subquery_expr && right_subquery_expr->have_row(&tuple)) { // 在非in非exists运算中，右子表达式只能输出一个值
    LOG_WARN("right expression is a subquery but output multiple rows in comparison.");
    return RC::INVALID_ARGUMENT;
  }

  bool bool_value = false;
  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }

  // 关闭子查询算子
  if (left_subquery_expr) {
    left_subquery_expr->close();
  }
  if (right_subquery_expr) {
    right_subquery_expr->close();
  }
  return rc;
}

RC ComparisonExpr::eval(Chunk &chunk, std::vector<uint8_t> &select)
{
  RC     rc = RC::SUCCESS;
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression in comparison. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression in comparison. rc=%s", strrc(rc));
    return rc;
  }
  if (left_column.attr_type() != right_column.attr_type()) {
    LOG_WARN("cannot compare columns with different types");
    return RC::INTERNAL;
  }
  if (left_column.attr_type() == AttrType::INTS) {
    rc = compare_column<int>(left_column, right_column, select);
  } else if (left_column.attr_type() == AttrType::FLOATS) {
    rc = compare_column<float>(left_column, right_column, select);
  } else {
    // TODO: support string compare
    LOG_WARN("unsupported data type %d", left_column.attr_type());
    return RC::INTERNAL;
  }
  return rc;
}

template <typename T>
RC ComparisonExpr::compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const
{
  RC rc = RC::SUCCESS;

  bool left_const  = left.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    compare_result<T, true, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else if (left_const && !right_const) {
    compare_result<T, true, false>((T *)left.data(), (T *)right.data(), right.count(), result, comp_);
  } else if (!left_const && right_const) {
    compare_result<T, false, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else {
    compare_result<T, false, false>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  }
  return rc;
}

RC ComparisonExpr::get_table_ptr(const Table **table_ptr) const
{
  if (left_->type() == ExprType::FIELD && right_->type() == ExprType::VALUE) {
    *table_ptr = static_cast<FieldExpr *>(left_.get())->field().table();
    return RC::SUCCESS;
  } else if (left_->type() == ExprType::VALUE && right_->type() == ExprType::FIELD) {
    *table_ptr = static_cast<FieldExpr *>(right_.get())->field().table();
    return RC::SUCCESS;
  } else if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    *table_ptr = nullptr;
    return RC::SUCCESS;
  } else {
    LOG_WARN("unsupported operation to get table pointer in comparison expression. left type=%d, right type=%d", left_->type(), right_->type());
    return RC::INVALID_ARGUMENT;
  }
}

RC ComparisonExpr::traverse_check(const std::function<RC(Expression *)> &check_func)
{
  RC rc = RC::SUCCESS;
  rc = left_->traverse_check(check_func);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to traverse check left expression in comparison expr. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->traverse_check(check_func);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to traverse check right expression in comparison expr. rc=%s", strrc(rc));
    return rc;
  }
  rc = check_func(this);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to check comparison expr. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    if (tmp_value.attr_type() == AttrType::NULLS) {
      value.set_type(AttrType::NULLS);
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

RC ConjunctionExpr::traverse_check(const std::function<RC(Expression *)> &check_func)
{
  RC rc = RC::SUCCESS;
  for (auto &child : children_) {
    rc = child->traverse_check(check_func);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to traverse check child expression in conjunction expr. rc=%s", strrc(rc));
      return rc;
    }
  }
  rc = check_func(this);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to check conjunction expr. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

bool ArithmeticExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (type() != other.type()) {
    return false;
  }
  auto &other_arith_expr = static_cast<const ArithmeticExpr &>(other);
  return arithmetic_type_ == other_arith_expr.arithmetic_type() && left_->equal(*other_arith_expr.left_) &&
         right_->equal(*other_arith_expr.right_);
}
AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::VECTORS || right_->value_type() == AttrType::VECTORS) {
    return AttrType::VECTORS;
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  value.set_type(target_type);
  if (left_value.attr_type() == AttrType::NULLS || right_value.attr_type() == AttrType::NULLS) {
    value.set_type(AttrType::NULLS);
    return rc;
  }
  switch (arithmetic_type_) {
    case Type::ADD: {
      Value::add(left_value, right_value, value);
    } break;

    case Type::SUB: {
      Value::subtract(left_value, right_value, value);
    } break;

    case Type::MUL: {
      Value::multiply(left_value, right_value, value);
    } break;

    case Type::DIV: {
      Value::divide(left_value, right_value, value);
    } break;

    case Type::NEGATIVE: {
      Value::negative(left_value, value);
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
RC ArithmeticExpr::execute_calc(
    const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const
{
  RC rc = RC::SUCCESS;
  switch (type) {
    case Type::ADD: {
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, AddOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, AddOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
    } break;
    case Type::SUB:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, SubtractOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, SubtractOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::MUL:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, MultiplyOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, MultiplyOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::DIV:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, DivideOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, DivideOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::NEGATIVE:
      if (attr_type == AttrType::INTS) {
        unary_operator<LEFT_CONSTANT, int, NegateOperator>((int *)left.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        unary_operator<LEFT_CONSTANT, float, NegateOperator>(
            (float *)left.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    default: rc = RC::UNIMPLEMENTED; break;
  }
  if (rc == RC::SUCCESS) {
    result.set_count(result.capacity());
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression in arithmetic. rc=%s", strrc(rc));
    return rc;
  }
  if (right_) { // 只有在非取反运算中右子表达式才非空
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression in arithmetic. rc=%s", strrc(rc));
      return rc;
    }
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
    return rc;
  }
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_column(left_column, right_column, column);
}

RC ArithmeticExpr::calc_column(const Column &left_column, const Column &right_column, Column &column) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  column.init(target_type, left_column.attr_len(), std::max(left_column.count(), right_column.count()));
  bool left_const  = left_column.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right_column.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    column.set_column_type(Column::Type::CONSTANT_COLUMN);
    rc = execute_calc<true, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (left_const && !right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<true, false>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (!left_const && right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, false>(left_column, right_column, column, arithmetic_type_, target_type);
  }
  return rc;
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to try to get value of left expression in arithmetic. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to try to get value of right expression in arithmetic. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::traverse_check(const std::function<RC(Expression *)> &check_func)
{
  RC rc = RC::SUCCESS;
  rc = left_->traverse_check(check_func);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to traverse check left expression in arithmetic expr. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->traverse_check(check_func);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to traverse check right expression in arithmetic expr. rc=%s", strrc(rc));
    return rc;
  }
  rc = check_func(this);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to check arithmetic expr. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

UnboundAggregateExpr::UnboundAggregateExpr(const char *aggregate_name, Expression *child)
    : aggregate_name_(aggregate_name), child_(child)
{}

////////////////////////////////////////////////////////////////////////////////
AggregateExpr::AggregateExpr(Type type, Expression *child) : aggregate_type_(type), child_(child) {}

AggregateExpr::AggregateExpr(Type type, unique_ptr<Expression> child) : aggregate_type_(type), child_(std::move(child))
{}

RC AggregateExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    rc = RC::INTERNAL;
  }
  return rc;
}

bool AggregateExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != type()) {
    return false;
  }
  const AggregateExpr &other_aggr_expr = static_cast<const AggregateExpr &>(other);
  return aggregate_type_ == other_aggr_expr.aggregate_type() && child_->equal(*other_aggr_expr.child());
}

unique_ptr<Aggregator> AggregateExpr::create_aggregator() const
{
  unique_ptr<Aggregator> aggregator;
  switch (aggregate_type_) {
    case Type::SUM: {
      aggregator = make_unique<SumAggregator>();
      break;
    }
    case Type::AVG: {
      aggregator = make_unique<AvgAggregator>();
      break;
    }
    case Type::MAX: {
      aggregator = make_unique<MaxAggregator>();
      break;
    }
    case Type::MIN: {
      aggregator = make_unique<MinAggregator>();
      break;
    }
    case Type::COUNT: {
      aggregator = make_unique<CountAggregator>();
      break;
    }
    default: {
      ASSERT(false, "unsupported aggregate type");
      break;
    }
  }
  return aggregator;
}

RC AggregateExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(name()), value);
}

RC AggregateExpr::type_from_string(const char *type_str, AggregateExpr::Type &type)
{
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "count")) {
    type = Type::COUNT;
  } else if (0 == strcasecmp(type_str, "sum")) {
    type = Type::SUM;
  } else if (0 == strcasecmp(type_str, "avg")) {
    type = Type::AVG;
  } else if (0 == strcasecmp(type_str, "max")) {
    type = Type::MAX;
  } else if (0 == strcasecmp(type_str, "min")) {
    type = Type::MIN;
  } else {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}

RC AggregateExpr::traverse_check(const std::function<RC(Expression *)> &check_func)
{
  RC rc = RC::SUCCESS;
  rc = child_->traverse_check(check_func);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to traverse check child expression in aggregate expr. rc=%s", strrc(rc));
    return rc;
  }
  rc = check_func(this);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to check aggregate expr. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

UnboundVectorExpr::UnboundVectorExpr(const char *vector_func_name, Expression *left, Expression *right)
    : vector_func_name_(vector_func_name), left_(left), right_(right)
{}

////////////////////////////////////////////////////////////////////////////////

VectorExpr::VectorExpr(Type type, Expression *left, Expression *right)
    : vector_func_type_(type), left_(left), right_(right)
{}

VectorExpr::VectorExpr(Type type, std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
    : vector_func_type_(type), left_(std::move(left)), right_(std::move(right))
{}

RC VectorExpr::type_from_string(const char *type_str, VectorExpr::Type &type)
{
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "l2_distance")) {
    type = Type::L2_DISTANCE;
  } else if (0 == strcasecmp(type_str, "cosine_distance")) {
    type = Type::COSINE_DISTANCE;
  } else if (0 == strcasecmp(type_str, "inner_product")) {
    type = Type::INNER_PRODUCT;
  } else {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}


RC VectorExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (!left_ || !right_) {
    LOG_WARN("left or right expression is null");
    return RC::INTERNAL;
  }

  Value left_value;
  Value right_value;
  Value real_left_value;  // 在parser阶段将向量解析为字符串，这里需要将字符串转换为向量
  Value real_right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression in vector function. rc=%s", strrc(rc));
    return rc;
  }
  if (left_value.attr_type() != AttrType::VECTORS) { // 对应ValueExpr，直接提取出来的Value可能是字符串类型
    rc = Value::cast_to(left_value, AttrType::VECTORS, real_left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to cast left value to vector. rc=%s", strrc(rc));
      return rc;
    }
  } else {
    real_left_value = left_value;
  }

  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression in vector function. rc=%s", strrc(rc));
    return rc;
  }
  if (right_value.attr_type() != AttrType::VECTORS) {
    rc = Value::cast_to(right_value, AttrType::VECTORS, real_right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to cast right value to vector. rc=%s", strrc(rc));
      return rc;
    }
  } else {
    real_right_value = right_value;
  }

  switch (vector_func_type_) {
    case Type::L2_DISTANCE: {
      rc = calc_l2_distance(real_left_value, real_right_value, value);
    } break;
    case Type::COSINE_DISTANCE: {
      rc = calc_cosine_distance(real_left_value, real_right_value, value);
    } break;
    case Type::INNER_PRODUCT: {
      rc = calc_inner_product(real_left_value, real_right_value, value);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported vector function type. %d", vector_func_type_);
    } break;
  }
  return rc;
}

RC VectorExpr::calc_l2_distance(const Value &left, const Value &right, Value &value)
{
  Value sub_value; // 获取向量差值
  sub_value.set_type(AttrType::VECTORS);
  Value::subtract(left, right, sub_value);

  Value inner_product_value; // 存储内积运算结果
  VectorExpr::calc_inner_product(sub_value, sub_value, inner_product_value); // 自己和自己的内积运算
  
  Value::square(inner_product_value, value); // 计算根号
  
  return RC::SUCCESS;
}

RC VectorExpr::calc_cosine_distance(const Value &left, const Value &right, Value &value)
{
  Value numerator; // 存储分子
  VectorExpr::calc_inner_product(left, right, numerator); // 分子为内积运算
  
  Value left_inner_product_value; // 存储左向量内积运算结果
  VectorExpr::calc_inner_product(left, left, left_inner_product_value); // 左向量和自己的内积运算
  
  Value left_value; // 存储左向量根号运算结果
  Value::square(left_inner_product_value, left_value); // 计算根号

  Value right_inner_product_value; // 存储右向量内积运算结果
  VectorExpr::calc_inner_product(right, right, right_inner_product_value); // 右向量和自己的内积运算
  
  Value right_value; // 存储右向量根号运算结果
  Value::square(right_inner_product_value, right_value); // 计算根号

  Value denominator; // 存储分母
  denominator.set_type(AttrType::FLOATS);
  Value::multiply(left_value, right_value, denominator); // 分母为两向量根号的乘积

  Value fraction_value; // 存储分数运算结果
  fraction_value.set_type(AttrType::FLOATS);
  Value::divide(numerator, denominator, fraction_value); // 分子除以分母

  float result = 1 - fraction_value.get_float();
  value.set_value(Value(result));
  
  return RC::SUCCESS;
}

RC VectorExpr::calc_inner_product(const Value &left, const Value &right, Value &value)
{
  Value multiply_value;
  multiply_value.set_type(AttrType::VECTORS);
  Value::multiply(left, right, multiply_value); // 计算向量乘积
  
  Value::vector_aggregation(multiply_value, value); // 获取乘积的聚合值
  
  return RC::SUCCESS;
}

RC VectorExpr::traverse_check(const std::function<RC(Expression *)> &check_func)
{
  RC rc = RC::SUCCESS;
  rc = left_->traverse_check(check_func);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to traverse check left expression in vector expr. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->traverse_check(check_func);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to traverse check right expression in vector expr. rc=%s", strrc(rc));
    return rc;
  }
  rc = check_func(this);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to check vector expr. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
SubQueryExpr::SubQueryExpr(std::unique_ptr<ParsedSqlNode> parsed_sql_node)
    : parsed_sql_node_(std::move(parsed_sql_node))
{}

SubQueryExpr::~SubQueryExpr() = default;

AttrType SubQueryExpr::value_type() const
{
  return select_stmt_->query_expressions()[0]->value_type();
}

ExprType SubQueryExpr::type() const
{
  return ExprType::SUBQUERY;
}

RC SubQueryExpr::get_value(const Tuple &tuple, Value &value) const
{
  physical_operator_->set_parent_tuple(&tuple); // 为子查询的算子树中每一个算子设置父查询中当前得到的元组
  RC rc = physical_operator_->next();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get next tuple in subquery expr. rc=%s", strrc(rc));
    return rc;
  }
  Tuple *current_tuple = physical_operator_->current_tuple();
  // 当查询结果中存在多列value为无效子查询
  if (current_tuple->cell_num() != 1) {
    LOG_WARN("the subquery result has multiple columns.");
    return RC::INVALID_ARGUMENT;
  } 
  // 在tuple组中，find_cell()方法用于根据TuplCellSpec类型中的表和字段元数据来得到对应索引下的value
  // cell_at()方法为find_cell()方法调用，用于直接根据索引获取当前tuple下对应索引的值
  return current_tuple->cell_at(0, value); // 直接获取结果元组中第一个字段的值
}

RC SubQueryExpr::generate_select_stmt(Db *db, const BinderContext &binder_context)
{
  RC rc = RC::SUCCESS;
  Stmt *stmt = nullptr;
  // rc = Stmt::create_stmt(db, *parsed_sql_node_, stmt);
  rc = SelectStmt::create(db, parsed_sql_node_->selection, stmt, binder_context);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create select stmt. rc=%s", strrc(rc));
    return rc;
  }
  if (stmt->type() != StmtType::SELECT) {
    LOG_WARN("the stmt type resolved from subquery is not select");
    return RC::INTERNAL;
  }
  select_stmt_ = std::unique_ptr<SelectStmt>(static_cast<SelectStmt *>(stmt));
  return rc;
}

RC SubQueryExpr::generate_logical_operator()
{
  RC rc = RC::SUCCESS;
  rc = LogicalPlanGenerator::create(select_stmt_.get(), logical_operator_);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create logical operator. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

RC SubQueryExpr::generate_physical_operator()
{
  RC rc = RC::SUCCESS;
  rc = PhysicalPlanGenerator::create(*logical_operator_, physical_operator_);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create physical operator. rc=%s", strrc(rc));
    return rc;
  }
  return rc;
}

bool SubQueryExpr::have_row(const Tuple *parent_tuple) const
{
  physical_operator_->set_parent_tuple(parent_tuple);

  return physical_operator_->next() != RC::RECORD_EOF;
}

RC SubQueryExpr::open(Trx *trx)
{
  return physical_operator_->open(trx);
}

RC SubQueryExpr::close()
{
  return physical_operator_->close();
}
