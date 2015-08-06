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
#ifndef QUERYINTERPRETER_H
#define QUERYINTERPRETER_H

#include <QSqlQuery>
#include <QSharedPointer>
#include <QRegularExpressionMatchIterator>
namespace CuteEntityManager {
class Query;
class QueryBuilder;
class Condition;
class Join;
class OrderBy;
class Expression;
class QueryInterpreter {
  public:
    QueryInterpreter(QSharedPointer<QueryBuilder> builder);
    QSqlQuery build(const Query &q);

  protected:
    QString buildSelect(const QList<Expression> &columns, const bool &distinct = false,
                        const QString &selectOption = "") const;
    QString buildFrom(const QStringList &from) const;
    QString buildJoin(const QList<Join> &joins) const;
    QString buildWhere(const QList<Condition> &conditions) const;
    QString buildGroupBy(const QStringList &groupBy) const;
    QString buildHaving(const QList<Condition> &conditions) const;
    QString buildOrderByAndLimit(QString sql, const QList<OrderBy> &orderBy,
                                 const quint64 &limit, const quint64 &offset) const;
    QString buildOrderBy(const QList<OrderBy> &columns) const;
    QString buildCondition(const QList<Condition> &conditions) const;
    QString buildCondition(const Condition &conditions) const;

  private:
    QSharedPointer<QueryBuilder> builder;

};




//QStringList select;
//QString selectOption = QStringLiteral("");
//bool distinct = false;
//QStringList from;
//QStringList groupBy;
//QStringList orderBy;
//QLinkedList<Condition> conditions;
//QList<Join> joins;
//QHash<QString, QVariant> params;
//uint limit = 0;
//uint offset = 0;



//protected $conditionBuilders = [
//       'NOT' => 'buildNotCondition',
//       'AND' => 'buildAndCondition',
//       'OR' => 'buildAndCondition',
//       'BETWEEN' => 'buildBetweenCondition',
//       'NOT BETWEEN' => 'buildBetweenCondition',
//       'IN' => 'buildInCondition',
//       'NOT IN' => 'buildInCondition',
//       'LIKE' => 'buildLikeCondition',
//       'NOT LIKE' => 'buildLikeCondition',
//       'OR LIKE' => 'buildLikeCondition',
//       'OR NOT LIKE' => 'buildLikeCondition',
//       'EXISTS' => 'buildExistsCondition',
//       'NOT EXISTS' => 'buildExistsCondition',
//   ];


}

#endif // QUERYINTERPRETER_H
