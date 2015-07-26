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
#ifndef CACHE_H
#define CACHE_H
#include <QHash>
#include <QWeakPointer>
#include <QSharedPointer>
#include "entityinstancefactory.h"
#include "entity.h"
#include "entityhelper.h"

namespace CuteEntityManager {
class Entity;
class Cache {
  public:
    Cache();
    QHash<QString, QWeakPointer<Entity> > getCache() const;
    bool contains(qint64 id, const QString &classname);
    bool contains(const QString &key);
    template<class T> bool contains(qint64 id) {
        bool ok = false;
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            ok = this->contains(id, QString(EntityHelper::getClassname(e)));
            delete e;
        }
        return ok;
    }
    void insert(QSharedPointer<Entity> &entity);
    void remove(const QSharedPointer<Entity> &entity);
    void remove(const qint64 &id, const QString &classname);
    template<class T> void remove(qint64 id) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            this->remove(id, QString(EntityHelper::getClassname(e)));
            delete e;
        }
    }

    QSharedPointer<Entity> get(qint64 id, const QString &classname);
    template<class T> QSharedPointer<Entity> get(qint64 id) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            return this->get(id, QString(EntityHelper::getClassname(e)));
            delete e;
        }
        return QSharedPointer<Entity>();
    }

  protected:
    QString generateKey(qint64 id, const QString &classname);
  private:
    QHash<QString, QWeakPointer<Entity>> cache;
};
}

#endif // CACHE_H
