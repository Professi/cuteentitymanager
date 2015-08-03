#include "queryinterpreter.h"
using namespace CuteEntityManager;


QueryInterpreter::QueryInterpreter(QSharedPointer<QueryBuilder> builder) {
    this->builder = builder;
}

QSqlQuery QueryInterpreter::interpretQuery(Query &q) {

}
