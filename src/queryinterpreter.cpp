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

QSqlQuery QueryInterpreter::build(Query &q) {
    QList<QString> clauses = QList<QString>();
    clauses.append(this->buildSelect(q, q.getSelect(), q.getDistinct(),
                                     q.getSelectOption()));
    clauses.append(this->buildFrom(q.getFrom()));
    clauses.append(this->buildJoin(q.getJoins()));
    clauses.append(this->buildWhere(q, q.getWhere()));
    clauses.append(this->buildGroupBy(q.getGroupBy()));
    clauses.append(this->buildHaving(q, q.getHaving()));
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

QString QueryInterpreter::buildSelect(Query &q,
                                      const QList<Expression> &columns,
                                      const bool &distinct, const QString &selectOption) const {
    QString sqlSelect = distinct ? ("SELECT " + this->builder->distinct()) :
                        "SELECT";
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
        q.appendParams(e.getParams());
        QString nExp = e.getExpression();
        if (e.getOnlyColumn()) {
            sqlSelect += this->builder->getSchema()->quoteColumnName(e.getExpression());
        } else if (!nExp.contains("(")) {
            QRegularExpression re =
                QRegularExpression(
                    QRegularExpression::escape("/^(.*?)(?i:\\s+as\\s+|\\s+)([\\w\\-_\\.]+)$/"));
            //re.optimize();
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
        clause += tables.at(var);
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
        if (!j.getExpression().getExpression().isEmpty()) {
            QString expression = j.getExpression().getExpression();
            int count = expression.count("=");
            if (count < 1) {
                expression = this->builder->getSchema()->quoteTableName(expression);
            } else if (count == 1) {
                QStringList list = expression.split("=");
                expression = this->builder->getSchema()->quoteColumnName(list.at(
                                 0).trimmed()) + " = ";
                expression += this->builder->getSchema()->quoteColumnName(list.at(1).trimmed());
            }
            sqlJoin += " ON " + expression;
        }
    }
    return sqlJoin;
}

QString QueryInterpreter::buildWhere(Query &q,
                                     const QList<Expression> &conditions)
const {
    QString where = this->buildCondition(q, conditions);
    return where.isEmpty() ? "" : ("WHERE " + where);
}

QString QueryInterpreter::buildGroupBy(const QStringList &groupBy) const {
    return groupBy.isEmpty() ? "" : "GROUP BY " + this->builder->buildColumns(
               groupBy);
}

QString QueryInterpreter::buildHaving(Query &q,
                                      const QList<Expression> &conditions) const {
    QString having = this->buildCondition(q, conditions);
    return having.isEmpty() ? "" : ("HAVING " + having);
}

QString QueryInterpreter::buildOrderByAndLimit(QString sql,
        const QList<OrderBy> &orderBy, const quint64 &limit,
        const quint64 &offset) const {
    QString sqlOrderBy = this->buildOrderBy(orderBy);
    if (!sqlOrderBy.isEmpty()) {
        sql += this->builder->getSeparator() + sqlOrderBy;
    }
    QString sqlLimit = this->builder->limit(limit, offset, false);
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

QString QueryInterpreter::buildCondition(Query &q,
        const QList<Expression> &conditions) const {
    if (conditions.isEmpty()) {
        return "";
    }
    QString sqlCondition = "";
    bool first = true;
    for (int i = 0; i < conditions.size(); ++i) {
        Expression exp = conditions.at(i);
        QString expression = exp.getExpression();
        if (!expression.isEmpty()) {
            if (first) {
                first = false;
            } else if (expression.at(0) != ' ') {
                sqlCondition += this->builder->getSeparator();
            }
        }
        sqlCondition += expression;
        q.appendParams(exp.getParams());
    }
    return sqlCondition;
}
