#ifndef CACHE_H
#define CACHE_H
#include <QHash>
#include <QWeakPointer>
#include <QSharedPointer>
#include "entityinstancefactory.h"
#include "entity.h"

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
            ok = this->contains(id, QString(e->getClassname()));
            delete e;
        }
        return ok;
    }
    void insert(QSharedPointer<Entity> entity);
    void remove(QSharedPointer<Entity> entity);
    void remove(const qint64 &id, const QString &classname);
    template<class T> void remove(qint64 id) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            this->remove(id, QString(e->getClassname()));
            delete e;
        }
    }

    QSharedPointer<Entity> get(qint64 id, const QString &classname);
    template<class T> QSharedPointer<Entity> get(qint64 id) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            return this->get(id, QString(e->getClassname()));
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
