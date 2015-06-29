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
    static Entity *createInstance(const QMetaObject *object);

    template<typename T>
    static Entity *createInstance() {
        return EntityInstanceFactory::createInstance(qMetaTypeId<T>());
    }

    //http://www.mimec.org/node/350
    template<typename T>
    static void registerClass()
    {
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }

    static Entity* createObject( const QByteArray& className)
    {
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        return (*constructor)();
    }

private:
    typedef Entity* (*Constructor)();

    template<typename T>
    static Entity* constructorHelper()
    {
        return new T();
    }

    static QHash<QByteArray, Constructor>& constructors()
    {
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }

protected:
    EntityInstanceFactory();
};
}
#endif // ENTITYINSTANCEFACTORY_H
