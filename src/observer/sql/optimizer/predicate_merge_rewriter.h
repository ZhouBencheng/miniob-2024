#pragma once

#include "sql/optimizer/rewrite_rule.h"

/**
 * @brief 将算子树中连续的谓词算子合并
 * @ingroup Rewriter
 */
class PredicateMergeRewriter : public RewriteRule
{
public:
  PredicateMergeRewriter() = default;
  virtual ~PredicateMergeRewriter() = default;

  RC rewrite(std::unique_ptr<LogicalOperator> &oper, bool &change_made) override;

private:
  RC merge_expr(std::unique_ptr<Expression> &src_expr, std::unique_ptr<Expression> &target_expr);
};
