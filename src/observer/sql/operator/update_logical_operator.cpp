#include "sql/operator/update_logical_operator.h"
#include "sql/expr/expression.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, std::vector<std::pair<Field *, std::unique_ptr<Expression>>> assignments)
    : table_(table), assignments_(std::move(assignments))
{}
