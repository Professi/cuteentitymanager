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
#include "condition.h"
#include "orderby.h"
using namespace CuteEntityManager;
Query::Query() {
    //this->select << Expression("*");
}

void Query::appendWhereCondition(const QString &condition) {
    this->where.append(Condition(condition));
}

void Query::appendWhereCondition(const Condition &condition) {
    this->where.append(condition);
}

void Query::setSelect(const QStringList &value) {
    for (int var = 0; var < value.size(); ++var) {
        this->appendSelect(value.at(var));
    }
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

void Query::appendHavingCondition(const QString &condition) {
    this->having.append(Condition(condition));
}

void Query::appendHavingCondition(const Condition &condition) {
    this->having.append(condition);
}

QList<Condition> Query::getWhere() const {
    return where;
}

void Query::setWhere(const QList<Condition> &value) {
    where = value;
}

QList<Condition> Query::getHaving() const {
    return having;
}

void Query::setHaving(const QList<Condition> &value) {
    having = value;
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
