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
#include "orderby.h"
using namespace CuteEntityManager;
Query::Query() {
    //this->select << Expression("*");
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
