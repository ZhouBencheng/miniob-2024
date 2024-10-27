#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/optimizer/join_pushdown_rewriter.h"
#include "sql/operator/predicate_logical_operator.h"
#include "storage/table/table.h"


RC JoinPushdownRewriter::rewrite(std::unique_ptr<LogicalOperator> &oper, bool &change_made)
{
    RC rc = RC::SUCCESS;
    if (oper->type() != LogicalOperatorType::JOIN) {
        return rc;
    }
    auto join_oper = static_cast<JoinLogicalOperator *>(oper.get());

    if (oper->children().size() != 2) {
        return rc;
    }

    std::unique_ptr<LogicalOperator> &left_child = oper->children()[0];
    std::unique_ptr<LogicalOperator> &right_child = oper->children()[1];

    if (left_child->type() != LogicalOperatorType::TABLE_GET || right_child->type() != LogicalOperatorType::TABLE_GET) {
        return rc;
    }

    if (left_child->type() == LogicalOperatorType::TABLE_GET) {
        auto left_table_get = static_cast<TableGetLogicalOperator *>(left_child.get());
        std::vector<std::unique_ptr<Expression>> pushdown_exprs;
        
        // 获取join算子中所有可以下推的表达式
        std::vector<std::unique_ptr<Expression>> &join_predicates = join_oper->predicates();
        for (auto &expr : join_predicates) {
            rc = get_exprs_can_pushdown(expr, pushdown_exprs, left_table_get->table());
            if (rc != RC::SUCCESS) {
                LOG_WARN("failed to get exprs can pushdown. rc=%s", strrc(rc));
                return rc;
            }
        }

        if (!pushdown_exprs.empty()) {
            change_made = true;
            left_table_get->set_predicates(std::move(pushdown_exprs));
        }

        // 在右算子分别是谓词算子或者连接算子的情况下，剩余的谓词表达式均可以下推到右边
        if (right_child->type() == LogicalOperatorType::PREDICATE) {
            auto right_predicate = static_cast<PredicateLogicalOperator *>(right_child.get());
            right_predicate->set_predicates(std::move(join_oper->predicates()));
        } else if (right_child->type() == LogicalOperatorType::JOIN) {
            auto right_join = static_cast<JoinLogicalOperator *>(right_child.get());
            right_join->set_predicates(std::move(join_oper->predicates()));
        }
    }
    if (right_child->type() == LogicalOperatorType::TABLE_GET) {
        auto right_table_get = static_cast<TableGetLogicalOperator *>(right_child.get());
        std::vector<std::unique_ptr<Expression>> pushdown_exprs;
        
        std::vector<std::unique_ptr<Expression>> &join_predicates = join_oper->predicates();
        for (auto &expr : join_predicates) {
            rc = get_exprs_can_pushdown(expr, pushdown_exprs, right_table_get->table());
            if (rc != RC::SUCCESS) {
                LOG_WARN("failed to get exprs can pushdown. rc=%s", strrc(rc));
                return rc;
            }
        }

        if (!pushdown_exprs.empty()) {
            change_made = true;
            right_table_get->set_predicates(std::move(pushdown_exprs));
        }
        
        if (left_child->type() == LogicalOperatorType::PREDICATE) {
            auto left_predicate = static_cast<PredicateLogicalOperator *>(left_child.get());
            left_predicate->set_predicates(std::move(join_oper->predicates()));
        } else if (left_child->type() == LogicalOperatorType::JOIN) {
            auto left_join = static_cast<JoinLogicalOperator *>(left_child.get());
            left_join->set_predicates(std::move(join_oper->predicates()));
        }
    }
    return rc;
}

// join算子中能够得到的比较表达式一定都是属性和常量或者常量和常量的组合
RC JoinPushdownRewriter::get_exprs_can_pushdown(
    std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &pushdown_exprs, const Table *table_ptr)
{
    RC rc = RC::SUCCESS;
    if (expr == nullptr) {
        return rc;
    }

    if (expr->type() != ExprType::COMPARISON) {
        return rc;
    }

    auto comparison_expr = static_cast<ComparisonExpr *>(expr.get());
    if (comparison_expr->left()->type() == ExprType::FIELD) {
        const Field &field = static_cast<FieldExpr *>(comparison_expr->left().get())->field();
        if (field.table() == table_ptr) {
            pushdown_exprs.emplace_back(std::move(expr));
        }
    } else if (comparison_expr->right()->type() == ExprType::FIELD) {
        const Field &field = static_cast<FieldExpr *>(comparison_expr->right().get())->field();
        if (field.table() == table_ptr) {
            pushdown_exprs.emplace_back(std::move(expr));
        }
    } else { // 两边都是常量的比较表达式，直接下推，注意需要深度拷贝
        pushdown_exprs.emplace_back(std::make_unique<ComparisonExpr>(comparison_expr->comp(), comparison_expr->left()->clone(), comparison_expr->right()->clone()));
    }

    return rc;
}
