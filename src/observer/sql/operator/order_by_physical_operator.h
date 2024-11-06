#pragma once

#include "sql/operator/physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/stmt/order_by_stmt.h"

class OrderByPhysicalOperator : public PhysicalOperator {
public:
    OrderByPhysicalOperator(std::vector<std::unique_ptr<OrderByUnit>> &&units, std::vector<std::unique_ptr<Expression>> &&exprs);

    virtual PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

    virtual RC open(Trx *trx) override;
    virtual RC next() override;
    virtual RC close() override;

    virtual Tuple *current_tuple() override;

    RC cache_and_sort_table();

private:
    std::vector<std::unique_ptr<OrderByUnit>> units_;
    SpliceTuple tuple_;
    std::vector<std::vector<Value>> values_;

    std::vector<int> order_idx_;
    std::vector<int>::iterator iter_;
};
