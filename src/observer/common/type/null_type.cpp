#include "common/type/null_type.h"

int NullType::compare(const Value &left, const Value &right) const
{
    return INT32_MAX;
}

int NullType::cast_cost(AttrType type)
{
    return INT32_MAX;
}