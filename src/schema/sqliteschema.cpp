#include "sqliteschema.h"

SqliteSchema::SqliteSchema() : parent() {

}

SqliteSchema::~SqliteSchema()
{

}


QString Database::sqliteTableList() {
    return "SELECT tbl_name FROM sqlite_master WHERE type='table';";
}
