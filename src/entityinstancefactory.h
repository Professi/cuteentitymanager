#ifndef ENTITYINSTANCEFACTORY_H
#define ENTITYINSTANCEFACTORY_H
#include <QString>
#include <QVariant>
#include <QHash>

namespace CuteEntityManager {
class Entity;
class EntityInstanceFactory {
  public:
    static Entity *createInstance(const char *className);
    static Entity *createInstance(int id);
    static Entity *createInstance(const char *className, const QHash<QString, QVariant> &attributes);
    static Entity *setAttributes(Entity *e, const QHash<QString, QVariant> &attributes, QHash<QString, QMetaProperty> metaprops);
    static Entity *setAttributes(Entity *e, const QHash<QString, QVariant> &attributes);
  protected:
    EntityInstanceFactory();
};
}
#endif // ENTITYINSTANCEFACTORY_H
