#include "sql/operator/order_by_logical_operator.h"
#include "sql/stmt/order_by_stmt.h"
#include "sql/expr/expression.h"

OrderByLogicalOperator::OrderByLogicalOperator(std::vector<std::unique_ptr<OrderByUnit>> &&units, std::vector<std::unique_ptr<Expression>> &&basic_exprs)
    : units_(std::move(units)), basic_exprs_(std::move(basic_exprs)) {}

OrderByLogicalOperator::~OrderByLogicalOperator() {}
