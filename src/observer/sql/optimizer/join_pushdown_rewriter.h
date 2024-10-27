#pragma once

#include "sql/optimizer/rewrite_rule.h"
#include <vector>
#include "sql/operator/logical_operator.h"

/**
 * @brief 将join算子的谓词下推到table get算子
 * @ingroup Rewriter
 */
class JoinPushdownRewriter : public RewriteRule
{
public:
  JoinPushdownRewriter() = default;
  virtual ~JoinPushdownRewriter() = default;

  RC rewrite(std::unique_ptr<LogicalOperator> &oper, bool &change_made) override;

private:
    RC get_exprs_can_pushdown(
        std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &pushdown_exprs, const Table *table_ptr);
};
