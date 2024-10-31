#pragma once

#include "sql/operator/logical_operator.h"

class Field;
class Value;
class Table;

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
    UpdateLogicalOperator(Table *table, Field *field, std::unique_ptr<Expression> expr, int value_amount);
    virtual ~UpdateLogicalOperator() = default;

    LogicalOperatorType  type() const override { return LogicalOperatorType::UPDATE; }
    Table               *table() const         { return table_; }
    Field               *field() const         { return field_; }
    std::unique_ptr<Expression> &expr()        { return expr_; }
    int                  value_amount() const  { return value_amount_; }

private:
    Table                      *table_              = nullptr;
    Field                      *field_              = nullptr;
    std::unique_ptr<Expression> expr_;
    int                         value_amount_       = 0;
};