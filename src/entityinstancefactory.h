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
    static Entity *createInstance(const QString &className);
    static Entity *createInstance(int metaTypeId);
    static Entity *createInstance(const char *className,
                                  const QHash<QString, QVariant> &attributes);
    static Entity *setAttributes(Entity *&e,
                                 const QHash<QString, QVariant> &attributes,
                                 QHash<QString, QMetaProperty> metaprops);
    static Entity *setAttributes(Entity *&e,
                                 const QHash<QString, QVariant> &attributes);
    static const QString extractEntityType(const QString &s);
    static Entity *newSuperClassInstance(const Entity *e);

    template<typename T>
    static Entity *createInstance() {
        return EntityInstanceFactory::createInstance(qMetaTypeId<T>());
    }
  protected:
    EntityInstanceFactory();
};
}
#endif // ENTITYINSTANCEFACTORY_H
