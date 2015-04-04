#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
#include "schema.h"

class QueryBuilder
{
public:
    QueryBuilder();
    ~QueryBuilder();
    bool createTable(QString tablename, QHash<QString, QString> tableDefinition);

};

#endif // QUERYBUILDER_H
