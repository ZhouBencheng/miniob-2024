#include "common/type/attr_type.h"
#include "common/value.h"
#include "common/log/log.h"
#include "common/type/vector_type.h"
#include "common/lang/vector_utils.h"

int VectorType::compare(const Value &left, const Value &right) const
{
    return 0;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
    return RC::UNIMPLEMENTED;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const
{
    return RC::UNIMPLEMENTED;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const
{
    return RC::UNIMPLEMENTED;
}

RC VectorType::to_string(const Value &val, string &result) const
{
    string ss;
    VectorType::Type type = VectorType::Type::INT;
    RC rc = val.get_vector_type(&type);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get vector type. type=%d", val.attr_type());
        return rc;
    }
    common::vector_to_string(val.value_.pointer_value_, val.length(), type, ss);
    result = ss;
    return RC::SUCCESS;
}