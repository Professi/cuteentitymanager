#ifndef HASMANY_H
#define HASMANY_H
#include <QSharedPointer>
#include "entity.h"
#include "schema.h"
#include "attribute.h"
#include "cache.h"
#include "entitymanager.h"
namespace CuteEntityManager {
class HasMany
{
public:
    HasMany(const QSharedPointer<Entity> &entity, const Relation &r, const QSharedPointer<Schema> schema);
    /**
     * @todo compare old values with new values if nothing has changed don't persist them
     */
    void persist(QVariant &property, QList<Entity *> &mergedObjects, const bool newItem, EntityManager *em);
    void resolve(const QSharedPointer<Entity> &entity, Attribute *&attr, Cache &cache, EntityManager *em);
    void persistMappedByRelation(const QList<QSharedPointer<Entity>> &list,
                                 QSqlQuery &q, const QSharedPointer<Entity> &entity,
                                 const QSharedPointer<Entity> &ptr, const Relation &r,
                                 const QString &tblName);
    void removeEntityList(QVariant &var, EntityManager *em);
    void missingTable(const QString &tblName);
protected:
    QSharedPointer<Entity> entity;
    Relation relation;
    QSharedPointer<Entity> target;
    QSharedPointer<Schema> schema;


};
}
#endif // HASMANY_H
