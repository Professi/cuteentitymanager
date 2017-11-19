#ifndef RESOLVER_H
#define RESOLVER_H
#include <QSqlQuery>
#include <QSharedPointer>
#include "database.h"

namespace CuteEntityManager {
class Resolver
{
public:
    Resolver(QSharedPointer<Database> db);
    QList<QHash<QString, QVariant>> convertQueryResult(QSqlQuery &q);
protected:
    QSharedPointer<Database> db;
};
}

#endif // RESOLVER_H
