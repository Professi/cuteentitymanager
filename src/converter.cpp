#include "converter.h"
#include "entityinstancefactory.h"
using namespace CuteEntityManager;

Converter::Converter()
{

}

QSharedPointer<Entity> Converter::convert(const QHash<QString, QVariant>
                                              &map, const char *classname, Cache &cache) {
    auto ptr = QSharedPointer<Entity>(map.isEmpty() ? nullptr : EntityInstanceFactory::createInstance(
                                                          classname, map));
    cache.insert(ptr);
    return ptr;
}

void Converter::convert(const QHash<QString, QVariant> &map,
                            QSharedPointer<Entity> &entity, Cache &cache) {
    cache.insert(entity);
    auto data = entity.data();
    EntityInstanceFactory::setAttributes(data, map);
}

QList<QSharedPointer<Entity>> Converter::convert(QList<QHash<QString, QVariant>> maps,
        const char *classname, Cache &cache) {
    auto list = QList<QSharedPointer<Entity>>();
    for (int var = 0; var < maps.size(); ++var) {
        auto ptr = this->convert(maps.at(var), classname,cache);
        list.append(ptr);
    }
    return list;
}
