#ifndef SQLITEQUERYBUILDER_H
#define SQLITEQUERYBUILDER_H
#include "../querybuilder.h"
namespace CuteEntityManager {
class SqliteQueryBuilder : public QueryBuilder
{
public:
    SqliteQueryBuilder(QSharedPointer<Schema> schema, QSharedPointer<Database> database);
    ~SqliteQueryBuilder();
};

}
#endif // SQLITEQUERYBUILDER_H
