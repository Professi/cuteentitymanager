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
#include "entityinstancefactory.h"
#include "entity.h"
#include "entityhelper.h"
#include <QMetaType>
#include <QDebug>
using namespace CuteEntityManager;

QHash<QByteArray, EntityInstanceFactory::Constructor>
EntityInstanceFactory::instance =
    QHash<QByteArray, EntityInstanceFactory::Constructor>();

EntityInstanceFactory::EntityInstanceFactory() {
}

Entity *EntityInstanceFactory::createInstance(const char *className) {
    QString s = QString(className);
    if (!s.contains("*")) {
        s.append("*");
    }
    auto ptr = EntityInstanceFactory::createInstance(QMetaType::type(
                   s.toUtf8().constData()));
    if (!ptr) {
        s.remove("*");
        ptr = EntityInstanceFactory::createObject(s.toUtf8());
    }
    return ptr;
}

Entity *EntityInstanceFactory::createInstance(const QString &className) {
    return EntityInstanceFactory::createInstance(className.toUtf8().constData());
}

Entity *EntityInstanceFactory::createInstance(int metaTypeId) {
    Entity *e = nullptr;
    if (metaTypeId != QMetaType::UnknownType) {
        auto metaObject = QMetaType::metaObjectForType(metaTypeId);
        if (metaObject) {
            e = qobject_cast<Entity *>(EntityInstanceFactory::createObject(metaObject->className()));
            if(!e) {
                e = qobject_cast<Entity *>(metaObject->newInstance());
                qDebug() << "Backup method for dynamic object creation was called. Maybe the class " +
                         QString(metaObject->className()) + " isn't registered?";
            }
        } else {
            void *newObj = QMetaType::create(metaTypeId);
            if (newObj) {
                e = static_cast<Entity *>(newObj);
            }
        }
    }
    return e;
}

Entity *EntityInstanceFactory::createInstance(const char *className,
        const QHash<QString, QVariant> &attributes) {
    Entity *e = EntityInstanceFactory::createInstance(className);
    EntityInstanceFactory::setAttributes(e, attributes);
    return e;
}

void EntityInstanceFactory::setAttributes(Entity *&e,
        const QHash<QString, QVariant> &attributes,
        QHash<QString, QMetaProperty> metaprops) {
    if (e) {
        auto iterator = attributes.constBegin();
        while (iterator != attributes.constEnd()) {
            if (metaprops.contains(iterator.key())) {
                QMetaProperty prop = metaprops.value(iterator.key());
                if (prop.isWritable()) {
                    if (prop.isEnumType()) {
                        prop.write(e, prop.enumerator().valueToKey(iterator.value().toInt()));
                    } else {
                        prop.write(e, iterator.value());
                    }
                } else {
                    qWarning() << prop.name() << "on Entity" << EntityHelper::getClassname(
                                   e) << "not writeable!";
                }
            } else {
                e->setProperty(iterator.key().toLatin1().data(), iterator.value());
            }
            ++iterator;
        }
    }
}

void EntityInstanceFactory::setAttributes(Entity *&e,
        const QHash<QString, QVariant> &attributes) {
    if (!attributes.isEmpty()) {
        auto metaprops = EntityHelper::getMetaProperties(e);
        EntityInstanceFactory::setAttributes(e, attributes, metaprops);
    }
}

const QString EntityInstanceFactory::extractEntityType(const QString &s) {
    QString r = "";
    const QString sptr = "QSharedPointer";
    if (s.contains(sptr)) {
        const int index = s.indexOf(sptr) + sptr.count() + 1;
        r = s.mid(index, s.indexOf(">", index) - index);
    } else {
        r = s;
    }
    return r;
}

Entity *EntityInstanceFactory::newSuperClassInstance(const Entity *e) {
    Entity *super = nullptr;
    if (e) {
        auto metaObject = e->metaObject()->superClass();
        if (QString(metaObject->className()) != QString("CuteEntityManager::Entity")) {
            super = EntityInstanceFactory::createInstance(metaObject->className());
        }
    }
    return super;
}

Entity *EntityInstanceFactory::createInstance(const QMetaObject *object) {
    auto o = object->newInstance();
    if(o) {
        return qobject_cast<Entity *>(o);
    }
    return EntityInstanceFactory::createInstance(object->className());
}

QList<QSharedPointer<Entity>> EntityInstanceFactory::castQVariantList(
QVariant &list) {
    return *reinterpret_cast<QList<QSharedPointer<Entity>>*>(list.data());
}

QSharedPointer<Entity> EntityInstanceFactory::castQVariant(
    QVariant &entity) {
    auto e = entity.value<QSharedPointer<Entity>>();
    if(!e) {
        auto ne = *static_cast<QSharedPointer<QObject>*>(entity.data());
        auto entityPtr = ne.objectCast<Entity>();
        if(entityPtr) {
            e = entityPtr;
        }
    }
    return e;
}

QStringList EntityInstanceFactory::getRegisteredClasses() {
    QStringList registered = QStringList();
    for (auto i = EntityInstanceFactory::instance.constBegin();
            i != EntityInstanceFactory::instance.constEnd(); ++i) {
        registered.append(i.key());
    }
    return registered;
}

Entity *EntityInstanceFactory::createInstance(Attribute *&attr) {
    return EntityInstanceFactory::createInstance(
               EntityInstanceFactory::extractEntityType(
                   attr->getMetaProperty().typeName()));
}
