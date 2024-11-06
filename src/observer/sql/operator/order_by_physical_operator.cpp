#include "sql/operator/order_by_physical_operator.h"

using CmpObj = std::pair<std::vector<Value>, int>;

OrderByPhysicalOperator::OrderByPhysicalOperator(std::vector<std::unique_ptr<OrderByUnit>> &&units, std::vector<std::unique_ptr<Expression>> &&exprs)
: units_(std::move(units))
{
    tuple_.set_expressions(std::move(exprs));
}

RC OrderByPhysicalOperator::open(Trx *trx)
{
    RC rc = RC::SUCCESS;
    if (children_.size() != 1) {
        LOG_WARN("order by operator should have only one child");
        return RC::INTERNAL;
    }

    rc = children_[0]->open(trx);
    if (rc != RC::SUCCESS) {
        LOG_WARN("failed to open child operator in order by operator");
        return rc;
    }

    return cache_and_sort_table();
}

RC OrderByPhysicalOperator::cache_and_sort_table()
{
    RC rc = RC::SUCCESS;
    // 缓存一行基本数值，放在values_中后清空，再缓存下一行
    std::vector<Value> basic_values(tuple_.get_exprs().size());
    // 缓存排序需要的数值序列，对应其原始行号  
    std::vector<CmpObj> cmp_objs;
    // 保存记录的原始行号
    int idx = 0;

    while (RC::SUCCESS == (rc = children_[0]->next())) {
        Tuple *tuple = children_[0]->current_tuple();

        // 首先获取排序需要的值
        std::vector<Value> cmp_obj;
        for (auto &unit : units_) {
            Value value;
            unit->get_expr()->get_value(*tuple, value);
            cmp_obj.emplace_back(value);
        }
        cmp_objs.emplace_back(cmp_obj, idx++);

        // 然后获取查询需要的基本值
        basic_values.clear();
        for (auto &expr : tuple_.get_exprs()) {
            Value value;
            expr->get_value(*tuple, value);
            basic_values.emplace_back(value);
        }
        values_.emplace_back(basic_values);
    }

    bool is_ascs[units_.size()];
    for (size_t i = 0; i < units_.size(); ++i) {
        is_ascs[i] = units_[i]->is_asc();
    }

    auto cmp = [&is_ascs](const CmpObj &lhs, const CmpObj &rhs) {
        ASSERT(lhs.first.size() == rhs.first.size(), "cmp obj size not equal");
        // sql语句中的排序规则按照前后顺序来表示字段优先级
        for (size_t i = 0; i < lhs.first.size(); ++i) {
            const Value &left_value = lhs.first[i];
            const Value &right_value = rhs.first[i];
            if (left_value.attr_type() == AttrType::NULLS && right_value.attr_type() == AttrType::NULLS) {
                continue;
            } else if (left_value.attr_type() == AttrType::NULLS) {
                return is_ascs[i];
            } else if (right_value.attr_type() == AttrType::NULLS) {
                return !is_ascs[i];
            } else if (left_value != right_value) {
                return is_ascs[i] ? left_value < right_value : left_value > right_value;
            }
        }
        return false;
    };
    std::sort(cmp_objs.begin(), cmp_objs.end(), cmp);

    for (auto &obj : cmp_objs) {
        order_idx_.emplace_back(obj.second);
    }
    iter_ = order_idx_.begin();

    return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next()
{
    if (iter_ == order_idx_.end()) {
        return RC::RECORD_EOF;
    }
    tuple_.set_values(values_[*iter_]);
    ++iter_;
    return RC::SUCCESS;
}


RC OrderByPhysicalOperator::close()
{
    return children_[0]->close();
}

Tuple *OrderByPhysicalOperator::current_tuple()
{
    return &tuple_;
}
