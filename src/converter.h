#ifndef CONVERTER_H
#define CONVERTER_H
#include <QSharedPointer>
#include <QSqlQuery>
#include "entity.h"
#include "cache.h"
namespace CuteEntityManager {
class Converter
{
public:
    Converter();
    QSharedPointer<Entity> convert(const QHash<QString, QVariant> &map,
                                   const char *classname, Cache &cache);
    void convert(const QHash<QString, QVariant> &map, QSharedPointer<Entity> &entity, Cache &cache);
    QList<QSharedPointer<Entity>> convert(QList<QHash<QString, QVariant>> maps,
                                          const char *classname, Cache &cache);
    template<class T, class X>
    static QList<QSharedPointer<T>> convertList(const QList<QSharedPointer<X>> &list) {
        QList<QSharedPointer<T>> newList = QList<QSharedPointer<T>>();
        for (int i = 0; i < list.size(); ++i) {
            newList.append(qSharedPointerObjectCast<T>(list.at(i)));
        }
        return newList;
    }
};
}

#endif // CONVERTER_H
