#include "entityhelper.h"
#include "entity.h"
#include "relation.h"
#include "cache.h"

using namespace CuteEntityManager;
EntityHelper::EntityHelper()
{

}


const QHash<QString, Relation> EntityHelper::getNonInheritedRelations(const Entity *entity) {
    auto relations = entity->getRelations();
    auto superObject = EntityInstanceFactory::newSuperClassInstance(entity);
    if (superObject) {
        auto superRelations = superObject->getRelations();
        auto iterator = superRelations.constBegin();
        while (iterator != relations.constEnd()) {
            if (relations.contains(iterator.key())) {
                relations.remove(iterator.key());
            }
            ++iterator;
        }
        delete superObject;
        superObject = nullptr;
    }
    return relations;
}


const QList<const QMetaObject *> EntityHelper::superClasses(const Entity *entity,bool
                                                            stopAtSingleTableInheritance) {
    QList<const QMetaObject *> classes = QList<const QMetaObject *>();
    auto superMetaObject = entity->metaObject()->superClass();
    if (entity->getInheritanceStrategy() == InheritanceStrategy::JOINED_TABLE) {
        Entity *e = nullptr;
        while (superMetaObject && QString(superMetaObject->className()) !=
               QString("CuteEntityManager::Entity")) {
            e = EntityInstanceFactory::createInstance(superMetaObject->className());
            if (e) {
                classes.append(superMetaObject);
                superMetaObject = superMetaObject->superClass();
                InheritanceStrategy s = e->getInheritanceStrategy();
                delete e;
                e = nullptr;
                if (stopAtSingleTableInheritance && s == InheritanceStrategy::PER_CLASS_TABLE) {
                    break;
                }
            } else {
                break;
            }
        }
    }
    return classes;
}

const QHash<QString, QMetaProperty> EntityHelper::getMetaProperties(const Entity *entity) {
    return EntityHelper::getMetaProperties(entity->metaObject());
}

const QHash<QString, QMetaProperty> EntityHelper::getSuperMetaProperties(const Entity *entity) {
    auto superMetaObjectPropertyMap = QHash<QString, QMetaProperty>();
    auto superMeta = entity->metaObject()->superClass();
    if (QString(superMeta->className()) != QString("CuteEntityManager::Entity")
            && entity->getInheritanceStrategy() == InheritanceStrategy::JOINED_TABLE) {
        for (int var = 0; var < superMeta->propertyCount(); ++var) {
            QMetaProperty prop = superMeta->property(var);
            if (prop.isReadable() && prop.isWritable()) {
                superMetaObjectPropertyMap.insert(QString(prop.name()), prop);
            }
        }
    }
    return superMetaObjectPropertyMap;
}

const QHash<QString, QMetaProperty> EntityHelper::getMetaProperties(
        const QMetaObject *object) {
    auto h = QHash<QString, QMetaProperty>();
    for (int var = 0; var < object->propertyCount(); ++var) {
        QMetaProperty m = object->property(var);
        if (m.isValid() && m.name() != QString("objectName")) {
            h.insert(m.name(), m);
        }
    }
    return h;
}

const QHash<QString, QMetaProperty> EntityHelper::getInheritedMetaProperties(const Entity *entity) {
    auto classes = EntityHelper::superClasses(entity);
    auto wholeProperties = QHash<QString, QMetaProperty>();
    for (int var = classes.size() - 1; var >= 0; --var) {
        auto metaObject = classes.at(var);
        auto properties = EntityHelper::getMetaProperties(metaObject);
        auto iterator = properties.constBegin();
        while (iterator != properties.constEnd()) {
            wholeProperties.insert(iterator.key(), iterator.value());
            ++iterator;
        }
    }
    return wholeProperties;
}

const QHash<Relation, QMetaProperty> EntityHelper::getRelationProperties(const Entity *entity) {
    auto h = QHash<Relation, QMetaProperty>();
    auto relations = entity->getRelations();
    for (int var = 0; var < entity->metaObject()->propertyCount(); ++var) {
        QMetaProperty m = entity->metaObject()->property(var);
        if (m.isValid() && relations.contains(QString(m.name()))) {
            h.insert(relations.value(m.name()), m);
        }
    }
    return h;
}

const char *EntityHelper::getClassname(const Entity *entity) {
    return entity->metaObject()->className();
}

const QString EntityHelper::getClassName(const Entity *entity)
{
    return QString(entity->metaObject()->className());
}

void EntityHelper::setListProperty(const QSharedPointer<Entity> &entity,
                                    QList<QSharedPointer<Entity> > &list,
                                    const QMetaProperty &property)  {
    QVariant var;
    var.setValue<QList<QSharedPointer<Entity>>>(list);
    property.write(entity.data(),var);
}

void EntityHelper::addEntityToListProperty(const QSharedPointer<Entity>
        &entity, QSharedPointer<Entity> add, const QMetaProperty &property) {
    QVariant var = property.read(entity.data());
    if (!var.isNull() && var.canConvert<QList<QVariant>>()) {
        auto list = EntityInstanceFactory::castQVariantList(var);
        if (!list.contains(add)) {
            list.append(add);
            EntityHelper::setListProperty(entity, list, property);
        }
    }
}

void EntityHelper::setProperty(const QSharedPointer<Entity> &entity,
                                QSharedPointer<Entity> value,
                                const QMetaProperty &property) {
    if (value && value->getProperty(value->getPrimaryKey()).toLongLong()
            > -1) {
        QVariant var;
        var.setValue<QSharedPointer<Entity>>(value);
        property.write(entity.data(), var);
    }
}

void EntityHelper::setProperty(const QSharedPointer<Entity> &entity, QSharedPointer<Entity> value, const QString property) {
    auto props = EntityHelper::getMetaProperties(entity.data());
    if(props.contains(property)) {
        QVariant var;
        var.setValue<QSharedPointer<Entity>>(value);
        entity->setProperty(property,var);
    }
}

QMetaProperty EntityHelper::mappedProperty(const Relation &r,
        const QSharedPointer<Entity> &foreignEntity) {
    QMetaProperty prop;
    auto props = EntityHelper::getMetaProperties(foreignEntity.data());
    if (!r.getMappedBy().isEmpty() && props.contains(r.getMappedBy())) {
        prop = props.value(r.getMappedBy());
    } else {
        auto relations = foreignEntity->getRelations();
        for (auto iterator = relations.constBegin(); iterator != relations.constEnd();
                ++iterator) {
            auto rel = iterator.value();
            if (rel.getMappedBy() == r.getPropertyName()) {
                prop = props.value(rel.getPropertyName());
                break;
            }
        }
    }
    return prop;
}
