#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
    UpdatePhysicalOperator(Table *table, Field *field, const Value *values, int value_amount)
    : table_(table), field_(field), values_(values), value_amount_(value_amount) {}

    virtual ~UpdatePhysicalOperator() = default;

    PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

    RC open(Trx *trx) override;
    RC next() override;
    RC close() override;

    Tuple *current_tuple() override { return nullptr; }
private:
    Table       *table_       = nullptr;
    Field       *field_       = nullptr;
    const Value *values_      = nullptr;
    int          value_amount_ = 0;
    Trx         *trx_         = nullptr;
    vector<Record> records_;
};