#ifndef QUERYINTERPRETER_H
#define QUERYINTERPRETER_H

#include <QSqlQuery>
#include <QSharedPointer>
namespace CuteEntityManager {
class Query;
class QueryBuilder;
class QueryInterpreter {
  public:
    QueryInterpreter(QSharedPointer<QueryBuilder> builder);
    QSqlQuery interpretQuery(Query &q);
  private:
    QSharedPointer<QueryBuilder> builder;
};
}

#endif // QUERYINTERPRETER_H
