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
#ifndef ENTITYHELPER_H
#define ENTITYHELPER_H
#include <QString>
#include <QHash>
#include <QMetaProperty>
#include "entity.h"
#include "entityinstancefactory.h"
#include "entity.h"
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
    static const QHash<QString, QMetaProperty> getNonInheritedMetaProperties(const Entity *entity);
    static const QHash<QString, QMetaProperty> getInheritedMetaProperties(
        const Entity *entity);
    static const QHash<Relation, QMetaProperty> getRelationProperties(
        const Entity *entity);
    static Entity* copyObject(const Entity *entity);


    static const char *getClassname(const Entity *entity);
    static const QString getClassName(const Entity *entity);
    static void addEntityToListProperty(const QSharedPointer<Entity> &entity,
                                        QSharedPointer<Entity> add, const QMetaProperty &property);
    static void removeEntityFromListProperty(const QSharedPointer<Entity> &entity,
            QSharedPointer<Entity> remove, const QMetaProperty &property);
    static void clearEntityListProperty(const QSharedPointer<Entity> &entity, const QMetaProperty &property);
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
    static QHash<QString, QVariant> getEntityAttributes(const
            QHash<QString, QMetaProperty>
            &props,
            const QSharedPointer<Entity> &entity);
};
}

#endif // ENTITYHELPER_H
