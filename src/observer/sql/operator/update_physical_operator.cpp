#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx) 
{
    // 要更新的表为空时直接返回
    if (children_.empty()) {
        return RC::SUCCESS;
    }

    std::unique_ptr<PhysicalOperator> &child = children_[0];

    RC rc = child->open(trx);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to open child operator: %s", strrc(rc));
        return rc;
    }

    trx_ = trx;

    while(OB_SUCC(rc = child->next())) { // 遍历下层算子提供的记录
        Tuple *tuple = child->current_tuple();
        std::unique_ptr<Value> value;
        RC rc = expr_->get_value(*tuple, *value);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to get value from tuple in update stmt. rc=%s", strrc(rc));
            return rc;
        }
        values_.emplace_back(std::move(value));

        if (nullptr == tuple) {
            LOG_WARN("failed to get current record: %s", strrc(rc));
            return rc;
        }
        RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
        Record   &record    = row_tuple->record();
        records_.emplace_back(record);
    }

    // 仿照DeletePhysicalOperator的做法
    // 先收集记录再进行更新
    // 记录的有效性由事务来保证，如果事务不保证更新的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
    for (size_t i = 0; i < records_.size(); i++) {
        rc = trx_->update_record(table_, records_[i], *values_[i], field_->meta());
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to update record: %s", strrc(rc));
            return rc;
        }
    }

    return RC::SUCCESS; 
}

RC UpdatePhysicalOperator::next() 
{
    return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close() 
{
    return RC::SUCCESS;
}