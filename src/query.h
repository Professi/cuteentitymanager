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

    QString getSelectOption() const;
    void setSelectOption(const QString &value);

    bool getDistinct() const;
    void setDistinct(bool value);

    QStringList getFrom() const;
    void setFrom(const QStringList &value);

    QList<Join> getJoins() const;
    void setJoins(const QList<Join> &value);

    void appendParam(const QString &column, QVariant value);
    QHash<QString, QVariant> getParams() const;
    void setParams(const QHash<QString, QVariant> &value);

    uint getLimit() const;
    void setLimit(const uint &value);

    uint getOffset() const;
    void setOffset(const uint &value);

    void appendWhereCondition(const QString &condition);
    void appendWhereCondition(const Condition &condition);

    void appendHavingCondition(const QString &condition);
    void appendHavingCondition(const Condition &condition);

    QList<Condition> getWhere() const;
    void setWhere(const QList<Condition> &value);

    QList<Condition> getHaving() const;
    void setHaving(const QList<Condition> &value);

    void appendOrderBy(const OrderBy &orderBy);
    void appendOrderBy(const QString &column, const Direction &direction);
    QList<OrderBy> getOrderBy() const;
    void setOrderBy(const QList<OrderBy> &value);

    QStringList getGroupBy() const;
    void setGroupBy(const QStringList &value);

    QList<Expression> getSelect() const;
    void appendSelect(const Expression &value);
    void appendSelect(const QString &value);
    void setSelect(const QList<Expression> &value);
    void setSelect(const QStringList &value);

private:
    QList<Expression> select;
    QString selectOption = QStringLiteral("");
    bool distinct = false;
    QStringList from;
    QStringList groupBy;
    QList<OrderBy> orderBy;
    QList<Condition> where;
    QList<Condition> having;
    QList<Join> joins;
    QHash<QString, QVariant> params;
    uint limit = 0;
    uint offset = 0;
};

enum class JokerPosition {
    FRONT, // e.g. "%foo"
    BEHIND, // e.g. "foo%"
    BOTH, // e.g. "%foo%"
    NONE
};


}

#endif // QUERY_H
