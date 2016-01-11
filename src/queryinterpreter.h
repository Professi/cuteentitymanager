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
class Join;
class OrderBy;
class Expression;
class AttributeResolver;
class QueryInterpreter {
  public:
    QueryInterpreter(QSharedPointer<AttributeResolver> ar);
    QSqlQuery build(Query &q, const QMetaObject *obj=nullptr);

  protected:
    QString buildSelect(Query &q, const QList<Expression> &columns,
                        const bool &distinct = false,
                        const QString &selectOption = "") const;
    QString buildFrom(const QStringList &from) const;
    QString buildJoin(const QList<Join> &joins) const;
    QString buildWhere(Query &q, const QList<Expression> &conditions) const;
    QString buildGroupBy(const QStringList &groupBy) const;
    QString buildHaving(Query &q, const QList<Expression> &conditions) const;
    QString buildOrderByAndLimit(QString sql, const QList<OrderBy> &orderBy,
                                 const quint64 &limit, const quint64 &offset) const;
    QString buildOrderBy(const QList<OrderBy> &columns) const;
    QString buildCondition(Query &q, const QList<Expression> &conditions) const;
    void convertParams(const QString &prefix,
                       QHash<QString, QVariant> &params, QString &condition, int &start) const;

  private:
    QSharedPointer<AttributeResolver> ar;

};

}

#endif // QUERYINTERPRETER_H
