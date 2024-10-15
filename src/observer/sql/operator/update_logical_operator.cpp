#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, Field *field, const Value *values, int value_amount)
    : table_(table), field_(field), values_(values), value_amount_(value_amount)
{}