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
#ifndef QUERY_H
#define QUERY_H
#include <QString>
#include <QHash>
#include <QVariant>
#include <QLinkedList>
#include "join.h"
#include "expression.h"

namespace CuteEntityManager {
class Condition;
class OrderBy;
enum class Direction;
class Query {
  public:
    Query();
    ~Query();
    Query(QStringList from, QList<Expression> where = QList<Expression>(),
          QList<Join> joins = QList<Join>(),
          QHash<QString, QVariant> params = QHash<QString, QVariant>(), quint64 limit = 0,
          quint64 offset = 0,
          QList<Expression> select = QList<Expression>(),
          QStringList groupBy = QStringList(), bool distinct = false,
          QList<Expression> having = QList<Expression>());

    QString getSelectOption() const;
    void setSelectOption(const QString &value);

    bool getDistinct() const;
    void setDistinct(bool value);

    void appendFrom(const QString &value);
    QStringList getFrom() const;
    void setFrom(const QStringList &value);

    void appendJoin(const Join &value);
    QList<Join> getJoins() const;
    void setJoins(const QList<Join> &value);

    void appendParam(const QString &column, QVariant value);
    void appendParams(const QHash<QString, QVariant> &params);
    QHash<QString, QVariant> getParams() const;
    void setParams(const QHash<QString, QVariant> &value);

    quint64 getLimit() const;
    void setLimit(const quint64 &value);

    quint64 getOffset() const;
    void setOffset(const quint64 &value);

    void appendOrderBy(const OrderBy &orderBy);
    void appendOrderBy(const QString &column, const Direction &direction);
    QList<OrderBy> getOrderBy() const;
    void setOrderBy(const QList<OrderBy> &value);

    void appendGroupBy(const QString &value);
    QStringList getGroupBy() const;
    void setGroupBy(const QStringList &value);

    QList<Expression> getSelect() const;
    void appendSelect(const Expression &value);
    void appendSelect(const QString &value);
    void setSelect(const QList<Expression> &value);
    void setSelect(const QStringList &value);

    void appendWhere(const QString &condition);
    void appendWhere(const Expression &condition);
    QList<Expression> getWhere() const;
    void setWhere(const QList<Expression> &value);

    void appendHaving(const QString &condition);
    void appendHaving(const Expression &condition);
    QList<Expression> getHaving() const;
    void setHaving(const QList<Expression> &value);

  private:
    QList<Expression> select;
    QString selectOption = QStringLiteral("");
    bool distinct = false;
    QStringList from;
    QStringList groupBy;
    QList<OrderBy> orderBy;
    QList<Expression> where;
    QList<Expression> having;
    QList<Join> joins;
    QHash<QString, QVariant> params;
    quint64 limit = 0;
    quint64 offset = 0;
};

enum class JokerPosition {
    FRONT, // e.g. "%foo"
    BEHIND, // e.g. "foo%"
    BOTH, // e.g. "%foo%"
    NONE
};


}

#endif // QUERY_H
