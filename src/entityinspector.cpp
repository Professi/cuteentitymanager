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

EntityInspector::EntityInspector() {
    this->initLogger();
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
    qInfo() << msg;
    this->logger->logMsg(msg);
    bool ok = true;
    for (int i = 0; i < classes.size(); ++i) {
        bool r = this->checkEntity(classes.at(i));
        if (!r) {
            msg = "###############################";
            msg += "\n";
            msg += classes.at(i) + " is erroneous!";
            msg += "\n";
            msg += "###############################\n";
            qWarning() << msg;
            ok = false;
        } else {
            msg = "Entity class " + classes.at(i) + " seems ok!\n";
            qInfo() << msg;
        }
        this->logger->logMsg(msg);
    }
    msg = QDateTime::currentDateTime().toString(Qt::ISODate) +
          " - End checking entities\n";
    qInfo() << msg;
    this->logger->logMsg(msg);
    return ok;
}

bool EntityInspector::checkEntity(QString name) {
    QString msg = "--------------------\n";
    msg += "Checking " + name + " now!\n";
    qDebug() << msg;
    auto entity = this->instantiateEntity(name, msg);
    bool ok = true;
    if (entity) {
        bool relations = this->verifyRelations(entity, msg);
        bool pk = this->checkPrimaryKey(entity, msg);
        this->verifyBlobAttributes(entity, msg);
        this->verifyTransientAttributes(entity, msg);
        ok = pk && relations;
    }
    this->logger->logMsg(msg);
    return ok;
}

Entity *EntityInspector::instantiateEntity(const QString name, QString &msg) {
    auto entity = EntityInstanceFactory::createInstance(name);
    QString internMsg = "";
    if (entity) {
        internMsg = name + " is instanceable!";
        qInfo() << internMsg;
    } else {
        internMsg = name + " is NOT instanceable!";
        qCritical() << internMsg;
    }
    msg += internMsg + "\n";
    return entity;
}

void EntityInspector::checkMetaProperties(QHash<QString, QMetaProperty>
        &metaProperties, QString &msg, bool &ok, QHash<QString, Relation> &relations) {
    for (auto i = metaProperties.constBegin(); i != metaProperties.constEnd();
            ++i) {
        QString typeName = QString(i.value().typeName());
        if (!i.value().isWritable()) {
            ok = false;
            msg += "Property " + i.key() + " is not writable!\n”";
        }
        if (!i.value().isReadable()) {
            ok = false;
            msg += "Property " + i.key() + " is not readable!\n”";
        }
        if (typeName.contains("QSharedPointer") && !relations.contains(i.key())) {
            ok = false;
            msg += "For attribute " + i.key() + " is no relation defined!\n";
        } else if (typeName.contains("QPointer")) {
            ok = false;
            msg += i.key() + " must use QSharedPointer.\n";
        }
    }
}


bool EntityInspector::verifyRelations(Entity *&entity, QString &msg) {
    bool ok = true;
    auto metaProperties = EntityHelper::getMetaProperties(entity);
    auto relations = entity->getRelations();
    QString iMsg = "";
    this->checkMetaProperties(metaProperties, iMsg, ok, relations);
    for (auto i = relations.constBegin(); i != relations.constEnd(); ++i) {
        if (!metaProperties.contains(i.key())) {
            iMsg += "For relation " + i.key() + " is no property.";
        } else {
            auto metaProperty = metaProperties.value(i.key());
            if (!QString(metaProperty.typeName()).contains("QSharedPointer")) {
                iMsg += "Property " + QString(metaProperty.name()) +
                        " must be a type like QList<QSharedPointer<T>> or simply QSharedPointer<T>";
            } else {
                auto var = metaProperty.read(entity);
                bool rel = this->checkRelation(var, i.value(), msg, metaProperty);
                if (!rel) {
                    ok = false;
                }
            }
        }
    }
    if (!iMsg.isEmpty()) {
        qCritical() << iMsg;
        msg += iMsg;
    }
    return ok;
}

void EntityInspector::verifyTransientAttributes(Entity *&entity, QString &msg) {
    auto metaProperties = EntityHelper::getMetaProperties(entity);
    auto relations = entity->getRelations();
    auto transientAttributes = entity->getTransientAttributes();
    auto blobs = entity->getBLOBColumns();
    QString iMsg = "";
    for (int i = 0; i < transientAttributes.size(); ++i) {
        QString attr = transientAttributes.at(i);
        if (!metaProperties.contains(attr)) {
            iMsg += "No transient attribute called " + attr + ".\n";
        }
        if (relations.contains(transientAttributes.at(i))) {
            iMsg += "A transient attribute should not be declared as relation: " +
                    attr + ".\n";
        }
        if (blobs.contains(attr)) {
            iMsg += "A transient attribute should not be declared as blob column: " + attr +
                    ".\n";
        }
    }
    if (!iMsg.isEmpty()) {
        qWarning() << iMsg;
        msg += iMsg;
    }

}

bool EntityInspector::checkRelation(const QVariant &entity,
                                    const Relation &r, QString &msg, const QMetaProperty &property) const {
    QString iMsg = "";
    bool many = r.getType() == RelationType::MANY_TO_MANY
                || r.getType() == RelationType::ONE_TO_MANY;
    QString propType = QString(property.type());
    bool canConvertList = entity.canConvert<QVariantList>() || (many
                          && propType.contains("QList"));
    if ((many && !canConvertList)) {
        iMsg = "Relation type of " + r.getPropertyName() +
               " must be MANY_TO_MANY or ONE_TO_MANY.\n";
        iMsg += "Or you can change the attribute type to QSharedPointer<T>.\n";
    } else if ((!many && canConvertList)) {
        iMsg = "Relation type of " + r.getPropertyName() +
               " must be MANY_TO_ONE or ONE_TO_ONE.\n";
        iMsg += "Or you can change the attribute type to QList<QSharedPointer<T>>.\n";
    }
    if (many && r.getType() == RelationType::ONE_TO_MANY
            && r.getMappedBy().isEmpty()) {
        iMsg += "Relation " + r.getPropertyName() +
                " needs a mappedBy attribute of the foreign class.\n";
    }
    if (!iMsg.isEmpty()) {
        msg += iMsg;
        qCritical() << iMsg;
        return false;
    }
    return true;
}

bool EntityInspector::checkPrimaryKey(Entity *&entity, QString &msg) {
    QString pk = entity->getPrimaryKey();
    auto metaprops = EntityHelper::getMetaProperties(entity);
    QString iMsg = "";
    bool ok = true;
    if (!metaprops.contains(pk)) {
        ok = false;
        iMsg = "Property " + pk +
               " for primary key not exists. Please check your getPrimaryKey() method!\n";
    }
    qCritical() << iMsg;
    msg += iMsg;
    return ok;
}

void EntityInspector::verifyBlobAttributes(Entity *&entity, QString &msg) {
    auto metaprops = EntityHelper::getMetaProperties(entity);
    auto blobs = entity->getBLOBColumns();
    QString iMsg = "";
    for (int i = 0; i < blobs.size(); ++i) {
        QString name = blobs.at(i);
        if (!metaprops.contains(name)) {
            iMsg += "For blob column " + name + " no property exists.\n";
        }
    }
    qWarning() << iMsg;
    msg += iMsg;
}

void EntityInspector::initLogger() {
    this->logger = new Logger(QDir::currentPath() + "/entity.log");
}
