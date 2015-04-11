#include "sqlitequerybuilder.h"


CuteEntityManager::SqliteQueryBuilder::SqliteQueryBuilder(QSharedPointer<CuteEntityManager::Schema> schema,
        QSharedPointer<CuteEntityManager::Database> database) : QueryBuilder(schema, database) {

}

CuteEntityManager::SqliteQueryBuilder::~SqliteQueryBuilder() {

}
