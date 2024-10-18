#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"

class Table;
class Db;

/**
 * @brief Drop table语句
 * @ingroup Statement
 */
class DropTableStmt : public Stmt 
{
public:
    DropTableStmt() = default;
    DropTableStmt(Table *table);
    
    StmtType type() const override { return StmtType::DROP_TABLE; }

public:
    static RC create(Db *db, DropTableSqlNode &drop_table, Stmt *&stmt);

public:
    Table *table() const { return table_; }

private:
    Table *table_ = nullptr;
};