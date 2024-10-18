#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
    UpdateLogicalOperator(Table *table, Field *field, const Value *values, int value_amount);
    virtual ~UpdateLogicalOperator() = default;

    LogicalOperatorType  type() const override { return LogicalOperatorType::UPDATE; }
    Table               *table() const         { return table_; }
    Field               *field() const         { return field_; }
    const Value         *values() const        { return values_; }
    int                  value_amount() const  { return value_amount_; }

private:
    Table *table_        = nullptr;
    Field *field_        = nullptr;
    const Value *values_ = nullptr;
    int    value_amount_ = 0;
};