#ifndef ENTITYHELPER_H
#define ENTITYHELPER_H
#include <QString>
#include <QHash>
#include <QMetaProperty>
namespace CuteEntityManager {

class Relation;
class Entity;
class Cache;
class EntityHelper {
  public:
    EntityHelper();
    static const QHash<QString, Relation> getNonInheritedRelations(
        const Entity *entity);
    static const QList<const QMetaObject *> superClasses(const Entity *entity,
            bool stopAtSingleTableInheritance
            = false);
    static const QHash<QString, QMetaProperty> getMetaProperties(
        const Entity *entity);
    static const QHash<QString, QMetaProperty> getSuperMetaProperties(
        const Entity *entity);
    static const QHash<QString, QMetaProperty> getMetaProperties(
        const QMetaObject *object);
    static const QHash<QString, QMetaProperty> getInheritedMetaProperties(
        const Entity *entity);
    static const QHash<Relation, QMetaProperty> getRelationProperties(
        const Entity *entity);

    static const char *getClassname(const Entity *entity);
    static const QString getClassName(const Entity *entity);
    static void addEntityToListProperty(const QSharedPointer<Entity> &entity,
                                        QSharedPointer<Entity> add, const QMetaProperty &property);
    static void setListProperty(const QSharedPointer<Entity> &entity,
                                QList<QSharedPointer<Entity>> &list,
                                const QMetaProperty &property);
    static void setProperty(const QSharedPointer<Entity> &entity,
                            QSharedPointer<Entity> value,
                            const QMetaProperty &property);
    static void setProperty(const QSharedPointer<Entity> &entity,
                            QSharedPointer<Entity> value,
                            const QString property);
    static QMetaProperty mappedProperty(const Relation &r,
                                        const QSharedPointer<Entity> &foreignEntity);
};
}

#endif // ENTITYHELPER_H
