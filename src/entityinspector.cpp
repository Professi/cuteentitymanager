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
#include "entityinspector.h"
#include <QDir>
#include <QDebug>
#include <QDateTime>
using namespace CuteEntityManager;

EntityInspector::EntityInspector(const MsgType msgType) {
    this->initLogger(msgType);
}

EntityInspector::~EntityInspector() {
    if (this->logger) {
        delete this->logger;
        this->logger = nullptr;
    }
}

bool EntityInspector::checkRegisteredEntities() {
    QStringList classes = EntityInstanceFactory::getRegisteredClasses();
    QString msg = QDateTime::currentDateTime().toString(Qt::ISODate) +
                  " - Start checking entities\n";
    this->logger->logMsg(msg, MsgType::INFO);
    bool ok = true;
    for (int i = 0; i < classes.size(); ++i) {
        bool r = this->checkEntity(classes.at(i));
        if (!r) {
            msg = "###############################";
            msg += "\n";
            msg += classes.at(i) + " is erroneous!";
            msg += "\n";
            msg += "###############################\n";
            this->logger->logMsg(msg, MsgType::CRITICAL);
            ok = false;
        } else {
            msg = "Entity class " + classes.at(i) + " seems ok.\n";
            this->logger->logMsg(msg, MsgType::INFO);
        }
    }
    msg = QDateTime::currentDateTime().toString(Qt::ISODate) +
          " - End checking entities\n";
    this->logger->logMsg(msg, MsgType::INFO);
    return ok;
}

bool EntityInspector::checkEntity(QString name) {
    QString msg = "--------------------\n";
    msg += "Checking " + name + " now.\n";
    this->logger->logMsg(msg, MsgType::DEBUG);
    auto entity = this->instantiateEntity(name);
    bool ok = true;
    if (entity) {
        bool relations = this->verifyRelations(entity);
        bool pk = this->checkPrimaryKey(entity);
        this->verifyBlobAttributes(entity);
        this->verifyTransientAttributes(entity);
        ok = pk && relations;
        delete entity;
        entity = nullptr;
    }
    return ok;
}

Entity *EntityInspector::instantiateEntity(const QString name) {
    auto entity = EntityInstanceFactory::createInstance(name);
    QString msg = "";
    if (entity) {
        msg = name + " is instantiable.";
        this->logger->logMsg(msg, MsgType::INFO);
    } else {
        msg = name + " is NOT instantiable!";
        this->logger->logMsg(msg, MsgType::CRITICAL);
    }
    return entity;
}

void EntityInspector::checkMetaProperties(QHash<QString, QMetaProperty>
        &metaProperties, bool &ok, QHash<QString, Relation> &relations) {
    QString msg = "";
    for (auto i = metaProperties.constBegin(); i != metaProperties.constEnd();
            ++i) {
        QString typeName = QString(i.value().typeName());
        if (!i.value().isWritable()) {
            ok = false;
            msg += "Property " + i.key() + " is not writable!\n";
        }
        if (!i.value().isReadable()) {
            ok = false;
            msg += "Property " + i.key() + " is not readable!\n";
        }
        if (typeName.contains("QSharedPointer") && !relations.contains(i.key())) {
            ok = false;
            msg += "No relation defined for attribute " + i.key() + "!\n";

        } else if (typeName.contains("QPointer")) {
            ok = false;
            msg += i.key() + " must use QSharedPointer.\n";
        }
    }
    this->logger->logMsg(msg, MsgType::CRITICAL);
}

bool EntityInspector::verifyRelations(Entity *&entity) {
    bool ok = true;
    auto metaProperties = EntityHelper::getMetaProperties(entity);
    auto relations = entity->getRelations();
    QString msg = "";
    this->checkMetaProperties(metaProperties, ok, relations);
    for (auto i = relations.constBegin(); i != relations.constEnd(); ++i) {
        this->checkRelationTypos(i.key(), i.value(), ok);
        if (!metaProperties.contains(i.key())) {
            msg += "For relation " + i.key() + " no property exists!";
            ok = false;
        } else {
            auto metaProperty = metaProperties.value(i.key());
            if (!QString(metaProperty.typeName()).contains("QSharedPointer")) {
                msg += "Property " + QString(metaProperty.name()) +
                       " must be a type like QList<QSharedPointer<T>> or simply QSharedPointer<T>.";
            } else {
                auto var = metaProperty.read(entity);
                bool rel = this->checkRelation(var, i.value(), metaProperty);
                if (!rel) {
                    ok = false;
                } else {
                    this->checkRelationMappings(metaProperty, i.value(), ok,entity);
                }
            }
        }
    }
    if (!msg.isEmpty()) {
        this->logger->logMsg(msg, MsgType::CRITICAL);
    }
    return ok;
}

void EntityInspector::verifyTransientAttributes(Entity *&entity) {
    auto metaProperties = EntityHelper::getMetaProperties(entity);
    auto relations = entity->getRelations();
    auto transientAttributes = entity->getTransientAttributes();
    auto blobs = entity->getBLOBColumns();
    QString msg = "";
    for (int i = 0; i < transientAttributes.size(); ++i) {
        QString attr = transientAttributes.at(i);
        if (!metaProperties.contains(attr)) {
            msg += "No transient attribute called " + attr + ".\n";
        }
        if (relations.contains(transientAttributes.at(i))) {
            msg += "A transient attribute should not be declared as relation: " +
                   attr + ".\n";
        }
        if (blobs.contains(attr)) {
            msg += "A transient attribute should not be declared as blob column: " + attr +
                   ".\n";
        }
    }
    if (!msg.isEmpty()) {
        this->logger->logMsg(msg, MsgType::WARNING);
    }
}

bool EntityInspector::checkRelation(const QVariant &entity,
                                    const Relation &r, const QMetaProperty &property) const {
    QString msg = "";
    bool many = r.getType() == RelationType::MANY_TO_MANY
                || r.getType() == RelationType::ONE_TO_MANY;
    QString propType = QString(property.type());
    bool canConvertList = entity.canConvert<QVariantList>() || (many
                          && propType.contains("QList"));
    if ((many && !canConvertList)) {
        msg = "Relation type of " + r.getPropertyName() +
              " must be MANY_TO_MANY or ONE_TO_MANY.\n Or you can change the attribute type to QSharedPointer<T>.\n";
    } else if ((!many && canConvertList)) {
        msg = "Relation type of " + r.getPropertyName() +
              " must be MANY_TO_ONE or ONE_TO_ONE.\n Or you can change the attribute type to QList<QSharedPointer<T>>.\n";
    }
    if (many && r.getType() == RelationType::ONE_TO_MANY
            && r.getMappedBy().isEmpty()) {
        msg += "Relation " + r.getPropertyName() +
               " needs a mappedBy attribute of the foreign class.\n";
    }
    if (!msg.isEmpty()) {
        this->logger->logMsg(msg, MsgType::CRITICAL);
        return false;
    }
    return true;
}

void EntityInspector::checkRelationTypos(const QString &name, const Relation &r,
        bool &ok) {
    if (name != r.getPropertyName()) {
        ok = false;
        this->logger->logMsg("Relation " + name + " has a typo.\n" + "Name " + name +
                             "and relation name " + r.getPropertyName() +
                             " are not equal.\n", MsgType::WARNING);
    }
}

void EntityInspector::checkRelationMappings(QMetaProperty &property,
        const Relation &r, bool &ok, Entity *&entity) {
    QString foreignEntityName = EntityInstanceFactory::extractEntityType(
                                    property.typeName());
    auto foreignInstance = EntityInstanceFactory::createInstance(foreignEntityName);
    if (foreignInstance) {
        auto foreignRelations = EntityHelper::getRelationProperties(foreignInstance);
        int foundMappedBy = 0;
        bool foundForeignMappedRelation = false;
        auto superClasses = EntityHelper::superClasses(entity,true);
        QStringList classNames = QStringList {EntityHelper::getClassName(entity)};
        for (int s = 0; s < superClasses.size(); ++s) {
           classNames.append(superClasses.at(s)->className());
        }
        for (auto i = foreignRelations.constBegin(); i != foreignRelations.constEnd();
                ++i) {
            if (r.getMappedBy().isEmpty()
                    && i.key().getMappedBy() == r.getPropertyName()) {
                for (int x = 0; x < classNames.size(); ++x) {
                    if(QString(i.value().typeName()).contains(classNames.at(x))) {
                        ++foundMappedBy;
                        break;
                    }
                }
            } else if (!r.getMappedBy().isEmpty()
                       && r.getMappedBy() == i.key().getPropertyName()) {
                foundForeignMappedRelation = true;
                break;
            }
        }
        if (r.getMappedBy().isEmpty()) {
            if (foundMappedBy == 0) {
                this->logger->logMsg("Optional: The relation " + r.getPropertyName() +
                                     " is not mapped in foreign class " + foreignEntityName +
                                     ". You could map it.\n", MsgType::INFO);
            } else if (foundMappedBy > 1) {
                this->logger->logMsg("The relation " + r.getPropertyName() +
                                     " is mapped several times (" +
                                     QString::number(foundMappedBy) + ") by foreign class " + foreignEntityName +
                                     ". You should map it only once!\n",
                                     MsgType::WARNING);
                ok = false;
            }
        } else if (!foundForeignMappedRelation) {
            this->logger->logMsg("Relation " + r.getPropertyName() +
                                 " with mappedBy attribute " +
                                 r.getMappedBy() + " has no mapped relation in " + foreignEntityName +
                                 " class!\n", MsgType::CRITICAL);
            ok = false;
        }
        delete foreignInstance;
        foreignInstance = nullptr;
    } else {
        this->logger->logMsg("Can't create object for property/relation " +
                             r.getPropertyName() +
                             "\n" + "Classname: " + foreignEntityName + "\n" + "Is the class registered?\n",
                             MsgType::CRITICAL);
        ok = false;
    }
}

bool EntityInspector::checkPrimaryKey(Entity *&entity) {
    QString pk = entity->getPrimaryKey();
    auto metaprops = EntityHelper::getMetaProperties(entity);
    bool ok = true;
    if (!metaprops.contains(pk)) {
        ok = false;
        this->logger->logMsg("Property " + pk +
                             " for primary key not exists. Please check your getPrimaryKey() method!\n",
                             MsgType::CRITICAL);
    }
    return ok;
}

void EntityInspector::verifyBlobAttributes(Entity *&entity) {
    auto metaprops = EntityHelper::getMetaProperties(entity);
    auto blobs = entity->getBLOBColumns();
    QString msg = "";
    for (int i = 0; i < blobs.size(); ++i) {
        QString name = blobs.at(i);
        if (!metaprops.contains(name)) {
            msg += "For blob column " + name + " no property exists.\n";
        }
    }
    this->logger->logMsg(msg, MsgType::WARNING);
}

void EntityInspector::initLogger(const MsgType msgType) {
    this->logger = new Logger(QDir::currentPath() + "/entity.log", msgType);
}
