/*
 * Copyright (C) 2015 Christian Ehringfeld <c.ehringfeld@t-online.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "query.h"
#include "entity.h"
#include "querybuilder.h"
using namespace CuteEntityManager;
Query::Query() {
}

Query::~Query() {
}

Query::Query(QStringList from, QList<Expression> where, QList<Join> joins,
             QHash<QString, QVariant> params, quint64 limit, quint64 offset,
             QList<Expression> select, QStringList groupBy, bool distinct,
             QList<Expression> having) {
    this->from = from;
    this->where = where;
    this->joins = joins;
    this->params = params;
    this->limit = limit;
    this->offset = offset;
    this->select = select;
    this->groupBy = groupBy;
    this->distinct = distinct;
    this->having = having;
}

Query::Query(QString from, Expression where, Join join,
             QHash<QString, QVariant> params, quint64 limit, quint64 offset,
             Expression select, QString groupBy, bool distinct, QList<Expression> having) {
    this->from.append(from);
    this->where.append(where);
    this->joins.append(join);
    this->params = params;
    this->limit = limit;
    this->offset = offset;
    this->select.append(select);
    this->groupBy.append(groupBy);
    this->distinct = distinct;
    this->having = having;
}

void Query::appendWhere(const QString &condition) {
    this->where.append(Expression(condition));
}

void Query::appendWhere(const Expression &condition) {
    this->where.append(condition);
}

void Query::setSelect(const QStringList &value) {
    for (int var = 0; var < value.size(); ++var) {
        this->appendSelect(value.at(var));
    }
}

QList<Expression> Query::getWhere() const {
    return where;
}

void Query::setWhere(const QList<Expression> &value) {
    where = value;
}

QList<Expression> Query::getHaving() const {
    return having;
}

void Query::setHaving(const QList<Expression> &value) {
    having = value;
}

Expression Query::whereCondition(const QSharedPointer<QueryBuilder> &qb, QString column,
                                 QVariant value) const {
    return qb->where(column, value);
}

Join Query::joinClasses(const QSharedPointer<QueryBuilder> &qb,
                        const QSharedPointer<Entity> &mainEntity, const QSharedPointer<Entity> &foreignEntity,
                        const QString &joinType) const {
    return qb->joinClasses(mainEntity, foreignEntity, joinType);
}

QList<Join> Query::joinBaseClasses(const QSharedPointer<QueryBuilder> &qb,
                                   const QSharedPointer<Entity> &entity) {
    return qb->joinBaseClasses(entity);
}

Expression Query::whereCondition(const QSharedPointer<QueryBuilder> &qb,
                                 QHash<QString, QVariant> conditions, QString conjunction) const {
    return qb->where(conditions, conjunction);
}

Expression Query::whereCondition(const QSharedPointer<QueryBuilder> &qb,
                                 QString condition, QHash<QString, QVariant> values) const {
    return qb->where(condition, values);
}

Expression Query::equal(const QSharedPointer<QueryBuilder> &qb, QString key,
                        QVariant value) const {
    return qb->equal(key, value);
}

Expression Query::notEqual(const QSharedPointer<QueryBuilder> &qb, QString key,
                           QVariant value) const {
    return qb->notEqual(key, value);
}

Expression Query::between(const QSharedPointer<QueryBuilder> &qb, QString column,
                          QVariant firstValue, QVariant secondValue) const {
    return qb->between(column, firstValue, secondValue);
}

Expression Query::notBetween(const QSharedPointer<QueryBuilder> &qb, QString column,
                             QVariant firstValue, QVariant secondValue) const {
    return qb->notBetween(column, firstValue, secondValue);
}

Expression Query::in(const QSharedPointer<QueryBuilder> &qb, QString column,
                     QList<QVariant> values) const {
    return qb->in(column, values);
}

Expression Query::notIn(const QSharedPointer<QueryBuilder> &qb, QString column,
                        QList<QVariant> values) const {
    return qb->notIn(column, values);
}

Expression Query::notOperator(const QSharedPointer<QueryBuilder> &qb, QString op,
                              QString column, QVariant value) const {
    return qb->notOperator(op, column, value);
}

Expression Query::orOperator(const QSharedPointer<QueryBuilder> &qb,
                             QHash<QString, QVariant> conditions, bool like) const {
    return qb->orOperator(conditions, like);
}

Expression Query::orOperator(const QSharedPointer<QueryBuilder> &qb) const {
    return qb->orOperator();
}

Expression Query::norOperator(const QSharedPointer<QueryBuilder> &qb) const {
    return qb->norOperator();
}

Expression Query::andOperator(const QSharedPointer<QueryBuilder> &qb,
                              QHash<QString, QVariant> conditions) const {
    return qb->andOperator(conditions);
}

Expression Query::andOperator(const QSharedPointer<QueryBuilder> &qb) const {
    return qb->andOperator();
}

Expression Query::nandOperator(const QSharedPointer<QueryBuilder> &qb) const {
    return qb->nandOperator();
}

Expression Query::arbitraryOperator(const QSharedPointer<QueryBuilder> &qb, QString op,
                                    QString column, QVariant value) const {
    return qb->arbitraryOperator(op, column, value);
}

Expression Query::isNull(const QSharedPointer<QueryBuilder> &qb, QString column) const {
    return qb->isNull(column);
}

Expression Query::isNotNull(const QSharedPointer<QueryBuilder> &qb,
                            QString column) const {
    return qb->isNotNull(column);
}

Expression Query::plainOr(const QSharedPointer<QueryBuilder> &qb) const {
    return qb->plainOr();
}

Expression Query::plainNor(const QSharedPointer<QueryBuilder> &qb) const {
    return qb->plainNor();
}

Expression Query::plainAnd(const QSharedPointer<QueryBuilder> &qb) const {
    return qb->plainAnd();
}

Expression Query::plainNand(const QSharedPointer<QueryBuilder> &qb) const {
    return qb->plainNand();
}

Expression Query::like(const QSharedPointer<QueryBuilder> &qb, QString column,
                       QVariant value, JokerPosition jp, QChar wildcard) {
    return qb->like(column, value, jp, wildcard);
}

Expression Query::like(const QSharedPointer<QueryBuilder> &qb,
                       QHash<QString, QVariant> conditions, QString conjunction, JokerPosition jp,
                       QChar wildcard) {
    return qb->like(conditions, conjunction, jp, wildcard);
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

void Query::appendFrom(const QString &value) {
    if (!this->from.contains(value)) {
        this->from.append(value);
    }
}

QStringList Query::getFrom() const {
    return from;
}

void Query::setFrom(const QStringList &value) {
    from = value;
}

void Query::appendJoinWith(const QString value) {
    Join j = Join(value);
    if (!this->joins.contains(j)) {
        this->joins.append(j);
    }
}

void Query::appendJoin(const Join &value) {
    if (!this->joins.contains(value)) {
        this->joins.append(value);
    }
}

void Query::appendJoins(const QList<Join> &value) {
    this->joins.append(value);
}

QStringList Query::getGroupBy() const {
    return groupBy;
}

void Query::setGroupBy(const QStringList &value) {
    groupBy = value;
}

QList<Expression> Query::getSelect() const {
    return this->select;
}

void Query::appendSelect(const Expression &value) {
    this->select.append(value);
}

void Query::appendSelect(const QString &value) {
    this->select.append(Expression(value, true));
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

void Query::appendParams(const QHash<QString, QVariant> &params) {
    for (auto i = params.constBegin(); i != params.constEnd(); ++i) {
        this->params.insert(i.key(), i.value());
    }
}

QHash<QString, QVariant> Query::getParams() const {
    return params;
}

void Query::setParams(const QHash<QString, QVariant> &value) {
    params = value;
}

quint64 Query::getLimit() const {
    return limit;
}

void Query::setLimit(const quint64 &value) {
    limit = value;
}

quint64 Query::getOffset() const {
    return offset;
}

void Query::setOffset(const quint64 &value) {
    offset = value;
}

void Query::appendHaving(const QString &condition) {
    this->having.append(Expression(condition));
}

void Query::appendHaving(const Expression &condition) {
    this->having.append(condition);
}

void Query::appendOrderBy(const OrderBy &orderBy) {
    this->orderBy.append(orderBy);
}

void Query::appendOrderBy(const QString &column, const Direction &direction) {
    this->orderBy.append(OrderBy(column, direction));
}

QList<OrderBy> Query::getOrderBy() const {
    return orderBy;
}

void Query::setOrderBy(const QList<OrderBy> &value) {
    orderBy = value;
}

void Query::appendGroupBy(const QString &value) {
    if (!this->groupBy.contains(value)) {
        this->groupBy.append(value);
    }
}
