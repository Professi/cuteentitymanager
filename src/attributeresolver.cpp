#include "attributeresolver.h"
#include "entityhelper.h"
#include "querybuilder.h"
#include <QDebug>
using namespace CuteEntityManager;

AttributeResolver::AttributeResolver(QSharedPointer<QueryBuilder> queryBuilder) {
    this->qb = queryBuilder;
}

AttributeResolver::~AttributeResolver() {
    this->qb = QSharedPointer<QueryBuilder>(nullptr);
    if(!this->attributes.isEmpty()) {
        QMutableHashIterator<QString, QHash<QString, Attribute*>> i(this->attributes);
        while(i.hasNext()) {
            i.next();
            auto embeddedHash = i.value();
            QMutableHashIterator<QString, Attribute*> i2(embeddedHash);
            while(i2.hasNext()) {
                i2.next();
                auto attr = i2.value();
                delete attr;
                i2.remove();
            }
            i.remove();
        }
    }
}

QHash<QString, QHash<QString, Attribute *>> AttributeResolver::getAttributes() const {
    return attributes;
}

void AttributeResolver::setAttributes(const QHash<QString, QHash<QString, Attribute*>>
                                      &value) {
    attributes = value;
}

Attribute *AttributeResolver::resolveManyToManyAttribute(const QSharedPointer<Entity> &e,
        const QString &attr, const Relation &r, const QSharedPointer<Entity> &target) {
    auto ptr = e;
    QString attributeName = r.getPropertyName();
    QString foreignColumnName = target->getTablename();
    auto baseObj = EntityHelper::getBaseClassObject(e, attributeName);
    Entity* foreignBaseObj = target.data();
    if (!r.getMappedBy().isEmpty()) {
        ptr = target;
        attributeName = r.getMappedBy();
        foreignBaseObj = EntityHelper::getBaseClassObject(ptr, attributeName);
        foreignColumnName = foreignBaseObj->getTablename();
    }
    Attribute *attrObj = new Attribute(attr,
                                       this->qb->generateColumnNameID(baseObj->getTablename()),
                                       baseObj->getTablename(), e->metaObject());
    this->resolveInheritance(e, attrObj);
    attrObj->setRelation(foreignBaseObj->getTablename(), target->metaObject(), r,
                         this->qb->generateManyToManyTableName((r.getMappedBy().isEmpty() ? baseObj->getTablename()
                                 : foreignBaseObj->getTablename()), attributeName),
                         this->qb->generateColumnNameID(foreignColumnName));
    delete baseObj;
    if(foreignBaseObj != target.data()) {
        delete foreignBaseObj;
    }
    return attrObj;
}

Attribute *AttributeResolver::resolveManyToOneAttribute(const QSharedPointer<Entity> &e,
        const QString &attr, const Relation &r, const QSharedPointer<Entity> &target) {
    Q_UNUSED(r);
    auto obj = EntityHelper::getBaseClassObject(e, attr);
    Attribute *attrObj = new Attribute(attr,
                                       this->qb->generateColumnNameID(attr),
                                       e->getTablename(), e->metaObject());
    this->resolveInheritance(e, attrObj);
    attrObj->setRelation(target->getTablename(), target->metaObject(), r, "", "id");
    delete obj;
    return attrObj;
}

Attribute *AttributeResolver::resolveOneToManyAttribute(const QSharedPointer<Entity> &e,
        const QString &attr, const Relation &r, const QSharedPointer<Entity> &target) {
    auto obj = EntityHelper::getBaseClassObject(e, attr);
    Attribute *attrObj = new Attribute(attr, "id",
                                       e->getTablename(), e->metaObject());
    this->resolveInheritance(e, attrObj);
    attrObj->setRelation(target->getTablename(), target->metaObject(), r, "",
                         this->qb->generateColumnNameID(r.getMappedBy()));
    delete obj;
    return attrObj;
}

Attribute *AttributeResolver::resolveNonRelatedAttribute(const QSharedPointer<Entity> &e,
        const QString &attr) {
    Attribute *obj = new Attribute(attr, attr, e->getTablename(), e->metaObject());
    this->resolveInheritance(e, obj);
    return obj;
}

const QMetaObject *AttributeResolver::resolveInheritance(const QSharedPointer<Entity> &e,
        Attribute *&attribute) {
    auto obj = EntityHelper::getBaseClassObject(e, attribute->getName());
    if(obj && obj->getTablename() != e->getTablename()) {
        attribute->setInheritance(obj->getTablename(), obj->metaObject());
    }
    return obj->metaObject();
}

void AttributeResolver::addAttribute(const QString &className, Attribute *&attr) {
    auto attrs = this->attributes.value(className);
    attrs.insert(attr->getName(), attr);
    this->attributes.insert(className, attrs);
}

Attribute *AttributeResolver::resolveExplicitAttribute(const QSharedPointer<Entity>
        &classObj, const QString &attribute, QSharedPointer<Entity> related) {
    Attribute* a = nullptr;
    if(classObj->getRelations().contains(attribute)) {
        auto relation = classObj->getRelations().value(attribute);
        if(relation.getType() == RelationType::MANY_TO_MANY) {
            a = this->resolveManyToManyAttribute(classObj, attribute, relation, related);
        } else if(relation.getType() == RelationType::MANY_TO_ONE ||
                  (relation.getType() == RelationType::ONE_TO_ONE && relation.getMappedBy().isEmpty())) {
            a = this->resolveManyToOneAttribute(classObj, attribute, relation, related);
        } else {
            a = this->resolveOneToManyAttribute(classObj, attribute, relation, related);
        }
    } else {
        a = this->resolveNonRelatedAttribute(classObj, attribute);
    }
    return a;
}

QSharedPointer<QueryBuilder> AttributeResolver::getQb() const {
    return qb;
}

bool AttributeResolver::containsAttribute(const QString &className,
        const QString &attribute) const {
    bool r = false;
    auto attributes = this->getAttributes();
    if(!this->attributes.isEmpty() && attributes.contains(className) &&
            !attributes.value(className).isEmpty() &&
            attributes.value(className).contains(attribute)) {
        r = true;
    }
    return r;
}

Attribute *AttributeResolver::resolveAttribute(const QString &className,
        const QString &attribute, const QString related) {
    Attribute *attr = nullptr;
    if(!className.isEmpty()) {
        if(this->containsAttribute(className, attribute)) {
            attr = this->attributes.value(className).value(attribute);
        } else {
            QSharedPointer<Entity> e = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                           className));
            QSharedPointer<Entity> rel = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                             related));
            attr = this->resolveExplicitAttribute(e, attribute, rel);
            this->addAttribute(className, attr);
        }
    }
    return attr;
}
