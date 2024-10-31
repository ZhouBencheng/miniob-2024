#include "sql/operator/update_logical_operator.h"
#include "sql/expr/expression.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, Field *field, std::unique_ptr<Expression> expr, int value_amount)
    : table_(table), field_(field), expr_(std::move(expr)), value_amount_(value_amount)
{}