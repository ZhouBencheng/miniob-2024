#pragma once

#include "sql/stmt/stmt.h"

class Db;
class Table;
class ExpressionBinder;

class OrderByUnit {
public:
    OrderByUnit(std::unique_ptr<Expression> &&expr, bool is_asc);
    ~OrderByUnit();

    std::unique_ptr<Expression> &get_expr()  { return expr_; }
    bool                         is_asc()    { return is_asc_; }

private:
    std::unique_ptr<Expression> expr_;
    bool is_asc_;
};

//////////////////////////////////////////////////////////////////////////////

class OrderByStmt : public Stmt {
public:
    OrderByStmt(std::vector<std::unique_ptr<OrderByUnit>> &&units, std::vector<std::unique_ptr<Expression>> &&basic_exprs);
    ~OrderByStmt() override;

    StmtType type() const override { return StmtType::ORDER_BY; }

    static RC create(Db *db, ExpressionBinder &expression_binder, OrderBySqlNode *nodes, int node_num, std::vector<std::unique_ptr<Expression>> &&proj_exprs, OrderByStmt *&stmt);

private:
    std::vector<std::unique_ptr<OrderByUnit>> units_;
    std::vector<std::unique_ptr<Expression>>  basic_exprs_;
};
