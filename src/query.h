#ifndef QUERY_H
#define QUERY_H
#include <QString>
#include <QHash>
#include <QVariant>
#include <QLinkedList>
#include "join.h"

namespace CuteEntityManager {
class Query
{
public:
    Query();
    QStringList getSelect() const;
    void setSelect(const QStringList &value);

    QString getSelectOption() const;
    void setSelectOption(const QString &value);

    bool getDistinct() const;
    void setDistinct(bool value);

    QStringList getFrom() const;
    void setFrom(const QStringList &value);

    QStringList getGroupBy() const;
    void setGroupBy(const QStringList &value);

    QStringList getOrderBy() const;
    void setOrderBy(const QStringList &value);

    QList<Join> getJoins() const;
    void setJoins(const QList<Join> &value);

    void appendParam(const QString &column, QVariant value);
    QHash<QString, QVariant> getParams() const;
    void setParams(const QHash<QString, QVariant> &value);

    uint getLimit() const;
    void setLimit(const uint &value);

    uint getOffset() const;
    void setOffset(const uint &value);

    QLinkedList<QString> getConditions() const;
    void appendCondition(const QString &condition);
    void setConditions(const QLinkedList<QString> &value);

private:
    QStringList select;
    QString selectOption = QStringLiteral("");
    bool distinct = false;
    QStringList from;
    QStringList groupBy;
    QStringList orderBy;
    QLinkedList<QString> conditions;
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
