#ifndef ATTRIBUTERESOLVER_H
#define ATTRIBUTERESOLVER_H
#include <QHash>
#include <QString>
#include "attribute.h"
#include "entity.h"
namespace CuteEntityManager {
class QueryBuilder;
class AttributeResolver {
  public:
    AttributeResolver(QSharedPointer<QueryBuilder> queryBuilder);
    virtual ~AttributeResolver();
    bool containsAttribute(const QString &className, const QString &attribute) const;
    Attribute* resolveAttribute(const QSharedPointer<Entity> &classObj,
                                const QString &attribute, QSharedPointer<Entity> related = QSharedPointer<Entity>());
    QHash<QString, QHash<QString, Attribute *>> getAttributes() const;
    void setAttributes(const QHash<QString, QHash<QString, Attribute *>> &value);
  protected:
    Attribute* resolveManyToManyAttribute(const QSharedPointer<Entity> &e,
                                          const QString &attr, const Relation &r, const QSharedPointer<Entity> &target);
    Attribute* resolveManyToOneAttribute(const QSharedPointer<Entity> &e, const QString &attr,
                                         const Relation &r, const QSharedPointer<Entity> &target);
    Attribute* resolveOneToManyAttribute(const QSharedPointer<Entity> &e, const QString &attr,
                                         const Relation &r, const QSharedPointer<Entity> &target);
    Attribute* resolveNonRelatedAttribute(const QSharedPointer<Entity> &e,
                                          const QString &attr);
    const QMetaObject *resolveInheritance(const QSharedPointer<Entity> &e,
                                          Attribute *&attribute);
    void addAttribute(const QString &className, Attribute *&attr);
    Attribute* resolveExplicitAttribute(const QSharedPointer<Entity> &classObj,
                                        const QString &attribute, QSharedPointer<Entity> related = QSharedPointer<Entity>());

  private:
    QSharedPointer<QueryBuilder> qb;
    QHash<QString, QHash<QString, Attribute*>> attributes;
};
}

#endif // ATTRIBUTERESOLVER_H
