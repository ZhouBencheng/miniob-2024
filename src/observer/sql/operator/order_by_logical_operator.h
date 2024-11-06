#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/stmt/order_by_stmt.h"

class OrderByLogicalOperator : public LogicalOperator {
public:
    OrderByLogicalOperator(std::vector<std::unique_ptr<OrderByUnit>> &&units, std::vector<std::unique_ptr<Expression>> &&basic_exprs);
    ~OrderByLogicalOperator() override;

    LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }

    std::vector<std::unique_ptr<OrderByUnit>> &units() { return units_; }
    std::vector<std::unique_ptr<Expression>> &basic_exprs() { return basic_exprs_; }

private:
    std::vector<std::unique_ptr<OrderByUnit>> units_;
    std::vector<std::unique_ptr<Expression>>  basic_exprs_;
};
