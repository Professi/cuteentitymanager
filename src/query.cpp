#include "query.h"
#include "condition.h"
using namespace CuteEntityManager;
Query::Query() {
    this->select << "*";
}

QStringList Query::getSelect() const {
    return select;
}

void Query::appendCondition(const QString &condition) {
    this->conditions.append(Condition(condition));
}

void Query::appendCondition(const Condition &condition) {
    this->conditions.append(condition);
}
QLinkedList<Condition> Query::getConditions() const {
    return conditions;
}

void Query::setConditions(const QLinkedList<Condition> &value) {
    conditions = value;
}

void Query::setSelect(const QStringList &value) {
    select = value;
}
QString Query::getSelectOption() const {
    return selectOption;
}

void Query::setSelectOption(const QString &value) {
    selectOption = value;
}
bool Query::getDistinct() const {
    return distinct;
}

void Query::setDistinct(bool value) {
    distinct = value;
}
QStringList Query::getFrom() const {
    return from;
}

void Query::setFrom(const QStringList &value) {
    from = value;
}
QStringList Query::getGroupBy() const {
    return groupBy;
}

void Query::setGroupBy(const QStringList &value) {
    groupBy = value;
}
QStringList Query::getOrderBy() const {
    return orderBy;
}

void Query::setOrderBy(const QStringList &value) {
    orderBy = value;
}
QList<Join> Query::getJoins() const {
    return joins;
}

void Query::setJoins(const QList<Join> &value) {
    joins = value;
}

void Query::appendParam(const QString &column, QVariant value) {
    this->params.insert(column, value);
}

QHash<QString, QVariant> Query::getParams() const {
    return params;
}

void Query::setParams(const QHash<QString, QVariant> &value) {
    params = value;
}

uint Query::getLimit() const {
    return limit;
}

void Query::setLimit(const uint &value) {
    limit = value;
}

uint Query::getOffset() const {
    return offset;
}

void Query::setOffset(const uint &value) {
    offset = value;
}
