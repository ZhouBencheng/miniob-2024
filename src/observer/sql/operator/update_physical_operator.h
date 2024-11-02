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
    UpdatePhysicalOperator(Table *table, std::vector<std::pair<Field *, std::unique_ptr<Expression>>> assignments)
    : table_(table), assignments_(std::move(assignments)) {}

    virtual ~UpdatePhysicalOperator() = default;

    PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

    RC open(Trx *trx) override;
    RC next() override;
    RC close() override;

    Tuple *current_tuple() override { return nullptr; }
private:
    Table                         *table_       = nullptr;
    std::vector<std::pair<Field *, std::unique_ptr<Expression>>> assignments_;
    Trx                           *trx_         = nullptr;
    vector<Record>                 records_; // 底层算子遍历提供的记录集合
    vector<vector<std::pair<Field *, std::unique_ptr<Value>>>> values_; // 一个记录对应一个要设置的值，因为子查询情况下根据tuple的不同可能会设置不同的值
};
