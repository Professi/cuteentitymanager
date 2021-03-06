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
#include "cache.h"
#include "entityhelper.h"
using namespace CuteEntityManager;
Cache::Cache() {
}
QHash<QString, QWeakPointer<Entity>> Cache::getCache() const {
    return cache;
}

bool Cache::contains(qint64 id, const QString &classname) {
    QString key = this->generateKey(id, classname);
    return this->contains(key);
}

bool Cache::contains(const QString &key) {
    if (!key.isEmpty()) {
        return this->cache.contains(key);
    }
    return false;
}

void Cache::clear() {
    this->cache.clear();
}

void Cache::insert(QSharedPointer<Entity> &entity) {
    if (entity && entity->getId() > -1) {
        QString key = this->generateKey(entity->getId(),
                                        EntityHelper::getClassName(entity.data()));
        if (this->cache.contains(key)) {
            QSharedPointer<Entity> ptr = this->cache.value(key).toStrongRef();
            if (ptr) {
                ptr.swap(entity);
                return;
            }
        }
        this->cache.insert(key, entity.toWeakRef());
    }
}

void Cache::remove(const QSharedPointer<Entity> &entity) {
    if (entity.data() && entity->getId() > -1) {
        this->remove(entity->getId(), EntityHelper::getClassName(entity.data()));
    }
}

void Cache::remove(const qint64 &id, const QString &classname) {
    this->cache.remove(this->generateKey(id, classname));
}

QSharedPointer<Entity> Cache::get(qint64 id, const QString &classname) {
    QString key = this->generateKey(id, classname);
    if (this->contains(key)) {
        QSharedPointer<Entity> ptr = this->cache.value(key).toStrongRef();
        if (!ptr) {
            this->remove(id, classname);
        }
        return ptr;
    }
    return QSharedPointer<Entity>();
}

QString Cache::generateKey(qint64 id, const QString &classname) const {
    if (id > -1) {
        return QString::number(id).append("[").append(classname).append("]");
    }
    return QString("");
}

