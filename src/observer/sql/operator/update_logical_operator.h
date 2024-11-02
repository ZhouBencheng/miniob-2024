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
    UpdateLogicalOperator(Table *table, std::vector<std::pair<Field *, std::unique_ptr<Expression>>> assignments);
    virtual ~UpdateLogicalOperator() = default;

    LogicalOperatorType  type() const override { return LogicalOperatorType::UPDATE; }
    Table               *table() const         { return table_; }
    std::vector<std::pair<Field *, std::unique_ptr<Expression>>> &assignments() { return assignments_; }

private:
    Table                      *table_              = nullptr;
    std::vector<std::pair<Field *, std::unique_ptr<Expression>>> assignments_;
};