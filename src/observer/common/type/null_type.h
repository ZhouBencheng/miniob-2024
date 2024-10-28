#pragma once 

#include "common/type/data_type.h"

class NullType : public DataType
{
public:
    NullType() : DataType(AttrType::NULLS) {}
    virtual ~NullType() {}

    int compare(const Value &left, const Value &right) const override;

    RC to_string(const Value &value, string &result) const override;
    
    int cast_cost(AttrType type) override;
};