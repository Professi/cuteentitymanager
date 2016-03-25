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
#include "attributeresolver.h"
#include "orderby.h"
#include "expression.h"
#include "schema.h"
#include "entityinstancefactory.h"
using namespace CuteEntityManager;


QueryInterpreter::QueryInterpreter(QSharedPointer<AttributeResolver> ar) {
    this->ar = ar;
}

QSqlQuery QueryInterpreter::build(Query &q, const QMetaObject *obj) {
    if(obj) {
        this->resolveRelations(q, obj);
    }
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
                sql += this->ar->getQb()->getSeparator();
            }
            sql += clause;
        }
    }
    sql = this->buildOrderByAndLimit(sql, q.getOrderBy(), q.getLimit(),
                                     q.getOffset());
    QSqlQuery sqlQuery = this->ar->getQb()->getQuery();
    sqlQuery.prepare(sql);
    this->ar->getQb()->bindValues(q.getParams(), sqlQuery, false);
    return sqlQuery;
}

QString QueryInterpreter::buildSelect(Query &q,
                                      const QList<Expression> &columns,
                                      const bool &distinct, const QString &selectOption) const {
    QString sqlSelect = distinct ? ("SELECT " + this->ar->getQb()->distinct() + " ") :
                        "SELECT ";
    if (!selectOption.isEmpty()) {
        sqlSelect += selectOption + " ";
    }
    if (columns.isEmpty()) {
        return sqlSelect + "*";
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
        auto params = e.getParams();
        this->convertParams(q, params, nExp);
        if (e.getOnlyColumn()) {
            sqlSelect += this->ar->getQb()->getSchema()->quoteColumnName(e.getExpression());
        } else if (!nExp.contains("(")) {
            QRegularExpression re =
                QRegularExpression(
                    QRegularExpression::escape("/^(.*?)(?i:\\s+as\\s+|\\s+)([\\w\\-_\\.]+)$/"));
#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
            re.optimize();
#endif
            QRegularExpressionMatchIterator iterator = re.globalMatch(nExp, 0,
                    QRegularExpression::PartialPreferFirstMatch);
            if (iterator.hasNext()) {
                for (int var = 0; var < 2; ++var) {
                    QRegularExpressionMatch match = iterator.next();
                    if (var == 1) {
                        sqlSelect += this->ar->getQb()->getSchema()->quoteColumnName(
                                         match.captured()) + " AS " + this->ar->getQb()->getSchema()->quoteColumnName("a" +
                                                 QString::number(i));
                    }
                }
            } else {
                nExp = this->ar->getQb()->getSchema()->quoteColumnName(nExp);
            }
        } else {
            sqlSelect += nExp + " AS " + this->ar->getQb()->getSchema()->quoteColumnName("a" +
                         QString::number(i));
        }
    }
    return sqlSelect;
}

QString QueryInterpreter::buildFrom(const QStringList &from) const {
    if (from.isEmpty()) {
        return "";
    }
    auto tables = this->ar->getQb()->quoteTableNames(from);
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
        sqlJoin += j.getType() + this->ar->getQb()->getSeparator() +
                   this->ar->getQb()->getSchema()->quoteTableName(j.getForeignTable());
        if (!j.getExpression().getExpression().isEmpty()) {
            QString expression = j.getExpression().getExpression();
            int count = expression.count("=");
            if (count < 1) {
                expression = this->ar->getQb()->getSchema()->quoteTableName(expression);
            } else if (count == 1) {
                QStringList list = expression.split("=");
                expression = this->ar->getQb()->getSchema()->quoteColumnName(list.at(
                                 0).trimmed()) + " = ";
                expression += this->ar->getQb()->getSchema()->quoteColumnName(list.at(1).trimmed());
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
    return groupBy.isEmpty() ? "" : "GROUP BY " + this->ar->getQb()->buildColumns(
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
        sql += this->ar->getQb()->getSeparator() + sqlOrderBy;
    }
    QString sqlLimit = this->ar->getQb()->limit(limit, offset, false);
    if (!sqlLimit.isEmpty()) {
        sql += this->ar->getQb()->getSeparator() + sqlLimit;
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
            sqlOrder += this->ar->getQb()->getSchema()->quoteColumnName(order.getColumn());
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
                sqlCondition += this->ar->getQb()->getSeparator();
            }
        }
        auto params = exp.getParams();
        this->convertParams(q, params, expression);
        sqlCondition += expression;
    }
    return sqlCondition;
}

QVariant QueryInterpreter::convertParamValue(const QVariant val) const {
    auto typeName = QString(val.typeName());
    QVariant r = val;
    if(typeName.contains("QSharedPointer")) {
        if(typeName.contains("QList")) {
            auto entities = EntityInstanceFactory::castQVariantList(r);
            QList<QVariant> ids;
            for (int i = 0; i < entities.size(); ++i) {
                if(entities.at(i)) {
                    ids.append(entities.at(i)->getProperty(entities.at(i)->getPrimaryKey()));
                }
            }
            r.setValue<QList<QVariant>>(ids);
        } else {
            auto entity = EntityInstanceFactory::castQVariant(r);
            if(entity && entity->getId() != -1) {
                r = entity->getProperty(entity->getPrimaryKey());
            }
        }
    }
    return r;
}

void QueryInterpreter::resolveRelations(Query &q, const QMetaObject *obj) {
    QList<Expression> expressions;
    expressions.append(q.getSelect());
    expressions.append(q.getWhere());
    foreach (QString groupBy, q.getGroupBy()) {
        expressions.append(Expression(groupBy));
    }
    expressions.append(q.getHaving());
    this->resolve(q, obj, expressions);
}

void QueryInterpreter::resolve(Query &q, const QMetaObject *obj,
                               QList<Expression> exp) {
}

void QueryInterpreter::convertParams(Query &q, const QHash<QString, QVariant> &params,
                                     QString &condition) const {
    for (auto i = params.begin(); i != params.end(); ++i) {
        QString key = this->generateParam(q);
        condition.replace(this->ar->getQb()->placeHolder(i.key()),
                          this->ar->getQb()->placeHolder(key));
        q.appendParam(key, this->convertParamValue(i.value()));
    }
}


QString QueryInterpreter::generateParam(Query &q) const {
    return "eP" + QString::number(q.getParams().size() + 1);
}
