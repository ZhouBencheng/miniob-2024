#include "sql/stmt/order_by_stmt.h"
#include "sql/stmt/stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/expr/expression.h"
#include "sql/parser/expression_binder.h"

OrderByUnit::OrderByUnit(std::unique_ptr<Expression> &&expr, bool is_asc)
    : expr_(std::move(expr)), is_asc_(is_asc) {}

OrderByUnit::~OrderByUnit() = default;

//////////////////////////////////////////////////////////////////////////////

OrderByStmt::OrderByStmt(std::vector<std::unique_ptr<OrderByUnit>> &&units, std::vector<std::unique_ptr<Expression>> &&basic_exprs)
    : units_(std::move(units)), basic_exprs_(std::move(basic_exprs)) {}

OrderByStmt::~OrderByStmt() = default;

RC OrderByStmt::create(Db *db, ExpressionBinder &expression_binder, OrderBySqlNode *nodes, int node_num, std::vector<std::unique_ptr<Expression>> &&proj_exprs, OrderByStmt *&stmt) {
    RC rc = RC::SUCCESS;
    std::vector<std::unique_ptr<OrderByUnit>> units;
    std::vector<std::unique_ptr<Expression>> bound_expressions;

    for (int i = 0; i < node_num; i++) {
        RC rc = expression_binder.bind_expression(nodes[i].expression, bound_expressions);
        if (rc != RC::SUCCESS) {
            LOG_WARN("failed to bind expression. rc=%s", strrc(rc));
            return rc;
        }
        units.emplace_back(new OrderByUnit(std::move(bound_expressions[i]), nodes[i].is_asc));
    }
    bound_expressions.clear();

    stmt = new OrderByStmt(std::move(units), std::move(proj_exprs));
    return rc;
}
