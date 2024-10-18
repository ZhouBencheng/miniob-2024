#include "sql/stmt/drop_table_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

DropTableStmt::DropTableStmt(Table *table) : table_(table) {}

RC DropTableStmt::create(Db *db, DropTableSqlNode &drop_table, Stmt *&stmt)
{
    const char *table_name = drop_table.relation_name.c_str();
    if (nullptr == db || nullptr == table_name)
    {
        LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
        return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
        LOG_WARN("no such table. db = %s, table_name = %s", db->name(), table_name);
        return RC::INVALID_ARGUMENT;
    }

    stmt = new DropTableStmt(table);
    return RC::SUCCESS;
}