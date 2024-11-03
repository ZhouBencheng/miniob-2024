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

        vector<std::pair<Field *, std::unique_ptr<Value>>> values_in_single_record; // 存储一个记录要改变的一系列值
        for (auto &assignment : assignments_) {
            std::unique_ptr<Expression> &expr = assignment.second;
            Value value;
            if (expr->type() == ExprType::SUBQUERY) { // 若赋值目标为子查询，则需要先打开子查询
                SubQueryExpr *subquery_expr = static_cast<SubQueryExpr *>(expr.get());
                subquery_expr->physical_operator()->set_parent_tuple(tuple);
                rc = subquery_expr->open(nullptr);
                if (rc != RC::SUCCESS) {
                    LOG_WARN("failed to open subquery expr. rc=%s", strrc(rc));
                    return rc;
                }
                rc = subquery_expr->get_value(*tuple, value);
                if (rc != RC::SUCCESS) {
                    LOG_WARN("failed to get value from subquery expr. rc=%s", strrc(rc));
                    return rc;
                }
                if (subquery_expr->have_row(tuple)) {
                    subquery_expr->close();
                    LOG_WARN("subquery expr has multiple rows. rc=%s", strrc(rc));
                    return RC::INVALID_ARGUMENT;
                }

                rc = subquery_expr->close();
                if (rc != RC::SUCCESS) {
                    LOG_WARN("failed to close subquery expr. rc=%s", strrc(rc));
                    return rc;
                }
            } else {
                rc = expr->get_value(*tuple, value);
                if (rc != RC::SUCCESS) {
                    LOG_WARN("failed to get value from tuple in update stmt. rc=%s", strrc(rc));
                    return rc;
                }
            }
            values_in_single_record.emplace_back(assignment.first, make_unique<Value>(value));
        }
        values_.emplace_back(std::move(values_in_single_record));

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
        for (auto &value_in_single_record : values_[i]) {
            rc = trx_->update_record(table_, records_[i], *value_in_single_record.second, value_in_single_record.first->meta());
            if (rc != RC::SUCCESS) {
                LOG_WARN("failed to update record: %s", strrc(rc));
                return rc;
            }
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