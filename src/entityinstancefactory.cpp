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
#include <QMetaType>
using namespace CuteEntityManager;
EntityInstanceFactory::EntityInstanceFactory() {

}

Entity *EntityInstanceFactory::createInstance(const char *className) {
    return EntityInstanceFactory::createInstance(QMetaType::type(className));
}

Entity *EntityInstanceFactory::createInstance(const QString &className) {
    return EntityInstanceFactory::createInstance(className.toUtf8().constData());
}

Entity *EntityInstanceFactory::createInstance(int metaTypeId) {
    Entity *e = 0;
    if (metaTypeId != -1) {
        e = static_cast<Entity *>(QMetaType::create(metaTypeId));
    }
    return e;
}

Entity *EntityInstanceFactory::createInstance(const char *className,
        const QHash<QString, QVariant> &attributes) {
    Entity *e = EntityInstanceFactory::createInstance(className);
    EntityInstanceFactory::setAttributes(e, attributes);
    return e;
}

Entity *EntityInstanceFactory::setAttributes(Entity *e,
        const QHash<QString, QVariant> &attributes,
        QHash<QString, QMetaProperty> metaprops) {
    if (e) {
        auto iterator = attributes.constBegin();
        while (iterator != attributes.constEnd()) {
            if (metaprops.contains(iterator.key())) {
                QMetaProperty prop = metaprops.value(iterator.key());
                if (!prop.isWritable() && !prop.write(e, iterator.value())) {
                    qDebug() << prop.name() << "on Entity" << e->getClassname() << "not writeable!";
                }
            }
            ++iterator;
        }
    }
    return e;
}

Entity *EntityInstanceFactory::setAttributes(Entity *e,
        const QHash<QString, QVariant> &attributes) {
    auto metaprops = e->getMetaProperties();
    return EntityInstanceFactory::setAttributes(e, attributes, metaprops);
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

Entity *EntityInstanceFactory::newSuperClassInstance(Entity *e) {
    Entity *super = 0;
    if (e) {
        auto metaObject = e->metaObject()->superClass();
        if (QString(metaObject->className()) != QString("Entity")) {
            super = EntityInstanceFactory::createInstance(metaObject->className());
        }
    }
    return super;
}
