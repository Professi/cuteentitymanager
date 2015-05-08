#include "cache.h"
using namespace CuteEntityManager;
Cache::Cache() {

}
QHash<QString, QWeakPointer<Entity> > Cache::getCache() const {
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

void Cache::insert(QSharedPointer<Entity> entity) {
    if (entity.data() && entity.data()->getId() > -1) {
        this->cache.insert(this->generateKey(entity.data()->getId(), QString(entity.data()->getClassname())),
                           entity.toWeakRef());
    }
}

void Cache::remove(QSharedPointer<Entity> entity) {
    if (entity.data() && entity.data()->getId() > -1) {
        this->remove(entity.data()->getId(), QString(entity.data()->getClassname()));
    }
}

void Cache::remove(const qint64 &id, const QString &classname) {
    this->cache.remove(this->generateKey(id, classname));
}

QSharedPointer<Entity> Cache::get(qint64 id, const QString &classname) {
    QString key = this->generateKey(id, classname);
    if (this->contains(key)) {
        return this->cache.value(key).toStrongRef();
    }
    return QSharedPointer<Entity>();
}

QString Cache::generateKey(qint64 id, const QString &classname) {
    if (id > -1) {
        return QString::number(id).append("[").append(classname).append("]");
    }
    return QString("");
}

