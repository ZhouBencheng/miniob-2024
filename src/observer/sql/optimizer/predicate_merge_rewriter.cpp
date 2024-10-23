#include "sql/optimizer/predicate_merge_rewriter.h"
#include "common/log/log.h"
#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"

RC PredicateMergeRewriter::rewrite(std::unique_ptr<LogicalOperator> &oper, bool &change_made)
{
  RC rc = RC::SUCCESS;
  if (oper->type() != LogicalOperatorType::PREDICATE) { // 对谓词算子进行优化
    return rc;
  }

  if (oper->children().size() != 1) { // 谓词算子必须有且只有一个子算子
    return rc;
  }

  std::unique_ptr<LogicalOperator> &child_oper = oper->children().front();
  if (child_oper->type() != LogicalOperatorType::PREDICATE) { // 对父子算子都是谓词算子的情形进行优化
    return rc;
  }

  std::vector<std::unique_ptr<Expression>> &src_exprs = oper->expressions();
  if (src_exprs.size() != 1) { // 保证父谓词算子中只有一个表达式(conjunction or comparison)
    return rc;
  }

  std::vector<std::unique_ptr<Expression>> &target_exprs = child_oper->expressions();
  if (target_exprs.size() != 1) { // 子谓词算子同理
    return rc;
  }

  std::unique_ptr<Expression> &src_expr = src_exprs.front();
  std::unique_ptr<Expression> &target_expr = target_exprs.front();

  // merge_expr函数将两个谓词算子都合并到子算子中
  rc = merge_expr(src_expr, target_expr);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to merge expr. rc=%s", strrc(rc));
    return rc;
  }

  ASSERT(!src_expr, "ERROR!");
  // 所有的表达式都合并到了下层算子
  // 这个predicate operator其实就可以不要了。但是这里没办法删除，弄一个空的表达式吧
  LOG_TRACE("all expressions of predicate operator were merged to child predicate operator, then make a fake one");

  Value value((bool)true);
  src_expr = std::unique_ptr<Expression>(new ValueExpr(value));

  change_made = true;
  return rc;
}

void extract_comparison_exprs(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &cmp_exprs) 
{
    if (expr->type() == ExprType::CONJUNCTION) {
        auto conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());
        ASSERT(conjunction_expr->conjunction_type() == ConjunctionExpr::Type::AND, "Unsupported conjunction type OR");
        std::vector<std::unique_ptr<Expression>> &children = conjunction_expr->children();
        cmp_exprs.insert(cmp_exprs.end(), 
                    std::make_move_iterator(children.begin()), 
                    std::make_move_iterator(children.end()));
        expr.reset();
    } else {
        cmp_exprs.emplace_back(std::move(expr));
    }
    return;
}

RC PredicateMergeRewriter::merge_expr(std::unique_ptr<Expression> &src_expr, std::unique_ptr<Expression> &target_expr)
{
  RC rc = RC::SUCCESS;
  std::vector<std::unique_ptr<Expression>> cmp_exprs;
  extract_comparison_exprs(src_expr, cmp_exprs);
  extract_comparison_exprs(target_expr, cmp_exprs);

  std::unique_ptr<Expression> merged_expr = std::make_unique<ConjunctionExpr>(ConjunctionExpr::Type::AND, std::move(cmp_exprs));
  std::swap(target_expr, merged_expr);
  return rc;
}
