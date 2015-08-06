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

#include "queryinterpreter.h"
#include "condition.h"
#include "join.h"
#include "query.h"
#include "querybuilder.h"
#include "orderby.h"
#include "expression.h"
#include "schema.h"
using namespace CuteEntityManager;


QueryInterpreter::QueryInterpreter(QSharedPointer<QueryBuilder> builder) {
    this->builder = builder;
}

QSqlQuery QueryInterpreter::build(const Query &q) {
    QList<QString> clauses = QList<QString>();
    clauses.append(this->buildSelect(q.getSelect(), q.getDistinct(),
                                     q.getSelectOption()));
    clauses.append(this->buildFrom(q.getFrom()));
    clauses.append(this->buildJoin(q.getJoins()));
    clauses.append(this->buildWhere(q.getWhere()));
    clauses.append(this->buildGroupBy(q.getGroupBy()));
    clauses.append(this->buildHaving(q.getHaving()));
    QString sql = "";
    bool first = true;
    for (int i = 0; i < clauses.size(); ++i) {
        QString clause = clauses.at(i);
        if (!clause.isEmpty()) {
            if (first) {
                first = false;
            } else {
                sql += this->builder->getSeparator();
            }
            sql += clause;
        }
    }
    sql = this->buildOrderByAndLimit(sql, q.getOrderBy(), q.getLimit(),
                                     q.getOffset());
    QSqlQuery sqlQuery = this->builder->getQuery();
    sqlQuery.prepare(sql);
    this->builder->bindValues(q.getParams(), sqlQuery, false);
    return sqlQuery;
}

QString QueryInterpreter::buildSelect(const QList<Expression> &columns,
                                      const bool &distinct, const QString &selectOption) const {
    QString sqlSelect = distinct ? "SELECT DISTINCT" : "SELECT";
    if (!selectOption.isEmpty()) {
        sqlSelect += this->builder->getSeparator() + selectOption;
    }
    if (columns.isEmpty()) {
        return sqlSelect + " *";
    }
    bool first = true;
    for (int i = 0; i < columns.size(); ++i) {
        if (first) {
            first = false;
        } else {
            sqlSelect += ", ";
        }
        Expression e = columns.at(i);
        QString nExp = e.getExpression();
        if (e.getOnlyColumn()) {
            sqlSelect += this->builder->getSchema()->quoteColumnName(e.getExpression());
        } else if (!nExp.contains("(")) {
            QRegularExpression re =
                QRegularExpression(
                    QRegularExpression::escape("/^(.*?)(?i:\\s+as\\s+|\\s+)([\\w\\-_\\.]+)$/"));
            re.optimize();
            QRegularExpressionMatchIterator iterator = re.globalMatch(nExp, 0,
                    QRegularExpression::PartialPreferFirstMatch);

            if (iterator.hasNext()) {
                for (int var = 0; var < 2; ++var) {
                    QRegularExpressionMatch match = iterator.next();
                    if (var == 1) {
                        sqlSelect += this->builder->getSchema()->quoteColumnName(
                                         match.captured()) + " AS " + this->builder->getSchema()->quoteColumnName("a" +
                                                 QString::number(i));
                    }
                }

            } else {
                nExp = this->builder->getSchema()->quoteColumnName(nExp);
            }
        } else {
            sqlSelect += nExp + " AS " + this->builder->getSchema()->quoteColumnName("a" +
                         QString::number(i));
        }
    }
    return sqlSelect;
}

QString QueryInterpreter::buildFrom(const QStringList &from) const {
    if (from.isEmpty()) {
        return "";
    }
    auto tables = this->builder->quoteTableNames(from);
    QString clause = "FROM ";
    bool first = true;
    for (int var = 0; var < tables.size(); ++var) {
        if (first) {
            first = false;
        } else {
            clause += ", ";
        }
        clause += from.at(var);
    }
    return clause;
}

QString QueryInterpreter::buildJoin(const QList<Join> &joins) const {
    if (joins.isEmpty()) {
        return "";
    }
    QString sqlJoin = "";
    for (int i = 0; i < joins.size(); ++i) {
        Join j = joins.at(i);
        sqlJoin += j.getType() + this->builder->getSeparator() +
                   this->builder->getSchema()->quoteTableName(j.getForeignTable());
        if (!j.getCondition().getConditions().isEmpty()) {
            QString condition = this->buildCondition(j.getCondition());
            if (!condition.isEmpty()) {
                sqlJoin += " ON " + condition;
            }
        }
    }
    return sqlJoin;
}

QString QueryInterpreter::buildWhere(const QList<Condition> &conditions)
const {
    QString where = this->buildCondition(conditions);
    return where.isEmpty() ? "" : ("WHERE " + where);
}

QString QueryInterpreter::buildGroupBy(const QStringList &groupBy) const {
    return groupBy.isEmpty() ? "" : "GROUP BY " + this->builder->buildColumns(
               groupBy);
}

QString QueryInterpreter::buildHaving(const QList<Condition> &conditions)
const {
    QString having = this->buildCondition(conditions);
    return having.isEmpty() ? "" : ("HAVING " + having);
}

QString QueryInterpreter::buildOrderByAndLimit(QString sql,
        const QList<OrderBy> &orderBy, const quint64 &limit,
        const quint64 &offset) const {
    QString sqlOrderBy = this->buildOrderBy(orderBy);
    if (!sqlOrderBy.isEmpty()) {
        sql += this->builder->getSeparator() + sqlOrderBy;
    }
    QString sqlLimit = this->builder->limit(limit, offset);
    if (!sqlLimit.isEmpty()) {
        sql += this->builder->getSeparator() + sqlLimit;
    }
    return sql;
}

QString QueryInterpreter::buildOrderBy(const QList<OrderBy> &columns) const {
    if (columns.isEmpty()) {
        return "";
    }
    bool first = true;
    QString sqlOrder = "ORDER BY ";
    for (int i = 0; i < columns.size(); ++i) {
        if (first) {
            first = false;
        } else {
            sqlOrder += ", ";
        }
        OrderBy order = columns.at(i);
        if (order.getColumn().isEmpty()) {
            sqlOrder += order.getExpressedDirection().getExpression();
        } else {
            sqlOrder += this->builder->getSchema()->quoteColumnName(order.getColumn());
            switch (order.getDirection()) {
            case Direction::SORT_ASC:
                sqlOrder += " ASC";
                break;
            case Direction::SORT_DESC:
                sqlOrder += " DESC";
                break;
            default:
                break;
            }
        }
    }
    return sqlOrder;
}

QString QueryInterpreter::buildCondition(const QList<Condition> &conditions)
const {
    if (conditions.isEmpty()) {
        return "";
    }
    return "";
}

QString QueryInterpreter::buildCondition(const Condition &conditions) const {
    return "";
}

