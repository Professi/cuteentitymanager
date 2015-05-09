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

#include "entitymanager.h"
#include "enums/databasetype.h"
#include "databasemigration.h"
using namespace CuteEntityManager;

QStringList EntityManager::connectionNames = QStringList();

void EntityManager::init() {
    auto schema = Database::getSchema(Database::getDatabaseType(
                                          this->db.data()->getDatabase().driverName()), this->db);
    this->schema = QSharedPointer<Schema>(schema);
    this->schema.data()->setTables(this->schema.data()->getTableSchemas());
}

EntityManager::EntityManager(QSqlDatabase database) {
    auto db = new Database(database);
    this->db = QSharedPointer<Database>(db);
    this->init();
}

bool EntityManager::startup(QString version, QStringList toInitialize) {
    DatabaseMigration *dbm = new DatabaseMigration();
    QSharedPointer<Entity> ptrDbm = QSharedPointer<Entity>(dbm);
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    bool ok = true;
    map.insert("version", version);
    if (this->findAllByAttributes(map, dbm->getTablename()).isEmpty()) {
        for (int var = 0; var < toInitialize.size(); ++var) {
            if (ok) {
                QString c = toInitialize.at(var);
                ok = this->createTable(QSharedPointer<Entity>(EntityInstanceFactory::createInstance(c)));
            } else {
                break;
            }
        }
        if (ok) {
            dbm->setVersion(version);
            dbm->setApplyTime(QDateTime::currentDateTime());
            this->create(ptrDbm);
        }
    }
    delete dbm;
    return ok;
}

EntityManager::EntityManager(const QString &databaseType, QString databasename , QString hostname, QString username,
                             QString password, QString port) {
    auto db = new Database(databaseType, this->createConnection(), hostname, databasename, username, password,
                           port.toInt());
    this->db = QSharedPointer<Database>(db);
    this->init();
}

bool EntityManager::checkTable(const QSharedPointer<Entity> &entity) {
    bool rc = true;
    if (!this->schema.data()->containsTable(entity.data()->getTablename())) {
        if (this->schema.data()->getQueryBuilder().data()->createTable(entity)) {
            this->schema.data()->getTableSchema(entity.data()->getTablename(), true);
            rc = this->schema.data()->getTables().contains(entity.data()->getTablename());
        }
    }
    return rc;
}

QSharedPointer<Database> EntityManager::getDb() const {
    return db;
}

void EntityManager::setDb(const QSharedPointer<Database> &value) {
    db = value;
}

QSharedPointer<Schema> EntityManager::getSchema() const {
    return schema;
}

void EntityManager::setSchema(const QSharedPointer<Schema> &value) {
    schema = value;
}

QString EntityManager::createConnection() {
    QStringList l = EntityManager::getConnectionNames();
    QString conName = "";
    bool ok = false;
    qint16 i = 0;
    while (!ok) {
        if (l.contains("con" + QString::number(i))) {
            ++i;
        } else {
            l.append("con" + QString::number(i));
            ok = true;
            conName = "con" + QString::number(i);
            EntityManager::setConnectionNames(l);
        }
    }
    return conName;
}

void EntityManager::removeConnectionName(const QString &name) {
    EntityManager::connectionNames.removeOne(name);
}

QSharedPointer<Entity> EntityManager::convert(const QHash<QString, QVariant> &map, const char *classname) {
    auto ptr = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(classname, map));
    this->cache.insert(ptr);
    return ptr;
}

QList<QSharedPointer<Entity> > EntityManager::convert(QList<QHash<QString, QVariant> > maps, const char *classname) {
    auto list = QList<QSharedPointer<Entity> >();
    for (int var = 0; var < maps.size(); ++var) {
        auto ptr = this->convert(maps.at(var), classname);
        list.append(ptr);
        this->cache.insert(ptr);
    }
    return list;
}

QList<QSharedPointer<Entity> > EntityManager::findEntityByAttributes(const QSharedPointer<Entity> &entity,
        bool ignoreID) {
    auto maps = this->findAllByAttributes(entity, ignoreID);
    return this->convert(maps, entity.data()->getClassname());
}

/**
 * @todo should be an insert statement with much values
 * not really usefull atm
 * @brief EntityManager::create
 * @param entities
 * @return
 */
bool EntityManager::create(QList<QSharedPointer<Entity> > entities) {
    bool ok = true;
    foreach (QSharedPointer<Entity> ent, entities) {
        ok = this->create(ent);
        if (!ok) {
            break;
        }
    }
    return ok;
}

/**
 * @TODO insert Relations
 * @brief EntityManager::create
 * @param entity
 * @return
 */
bool EntityManager::create(QSharedPointer<Entity> &entity) {
    bool rc = false;
    if (this->checkTable(entity) && this->count(entity) == 0) {
        QSqlQuery q = this->schema.data()->getQueryBuilder().data()->create(entity);
        rc = this->db->transaction(q);
        if (rc) {
            entity.data()->setId(this->schema.data()->getLastInsertID().toLongLong(&rc));
            this->cache.insert(entity);
        }
    }
    return rc;
}

EntityManager::~EntityManager() {
    EntityManager::removeConnectionName(this->db->getConnectionName());
}

QStringList EntityManager::getConnectionNames() {
    return EntityManager::connectionNames;
}

QHash<QString, QVariant> EntityManager::findById(qint64 id, QString tblname) {
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->find(id, tblname);
    this->db->select(q);
    QSqlRecord rec = q.record();
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    if (q.next()) {
        for (int var = 0; var < rec.count(); ++var) {
            QVariant variant = rec.value(var);
            if (variant.isValid()) {
                map.insert(rec.fieldName(var), variant);
            }
        }
    }
    return map;
}


QList<QHash<QString, QVariant> > EntityManager::findAllByAttributes(const QSharedPointer<Entity> &entity,
        bool ignoreID) {
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->findByAttributes(entity, ignoreID);
    return this->convertQueryResult(q);
}

QList<QHash <QString, QVariant> > EntityManager::findAllByAttributes(const QHash<QString, QVariant> &m,
        const QString &tblname,
        bool ignoreID) {
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->findByAttributes(m,
                  tblname, ignoreID);
    return this->convertQueryResult(q);
}

/**
 * @TODO insert Relations
 * @brief EntityManager::merge
 * @param entity
 * @param withRelations
 * @return
 */
bool EntityManager::merge(QSharedPointer<Entity> &entity, bool withRelations) {
    if (this->count(entity) == 0 && entity->getId() != -1) {
        QSqlQuery q = this->schema.data()->getQueryBuilder().data()->merge(entity);
        return this->db->transaction(q);
    } else {
        return false;
    }
}


QList<QHash<QString, QVariant> > EntityManager::convertQueryResult(QSqlQuery &q) {
    QList<QHash <QString, QVariant> > listmap = QList<QHash <QString, QVariant> >();
    this->db->select(q);
    QSqlRecord rec = q.record();
    QStringList l = QStringList();
    qint16 field_count = rec.count();
    for (int var = 0; var < field_count; ++var) {
        l.append(rec.fieldName(var));
    }
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    while (q.next()) {
        for (int var = 0; var < field_count; ++var) {
            map.insert(l.at(var), q.value(rec.indexOf(l.at(var))));
        }
        listmap.append(map);
    }
    return listmap;
}

QList<QHash <QString, QVariant> > EntityManager::findAll(QString tblname) {
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->findAll(tblname);
    return this->convertQueryResult(q);
}

bool EntityManager::save(QSharedPointer<Entity> &entity) {
    if (entity.data()->getId() > -1) {
        return this->merge(entity);
    } else {
        return this->create(entity);
    }
}

qint64 EntityManager::findId(QSharedPointer<Entity> &entity) {
    qint64 r = -1;
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->findId(entity);
    this->db->select(q);
    if (q.next()) {
        r = q.value(0).toLongLong();
    }
    return r;
}


bool EntityManager::remove(QSharedPointer<Entity> &entity) {
    bool rc = false;
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->remove(entity);
    if (this->db->transaction(q)) {
        this->cache.remove(entity);
        entity.clear();
        rc = true;
    }
    return rc;
}

bool EntityManager::createTable(const QSharedPointer<Entity> &entity) {
    return this->schema.data()->getQueryBuilder().data()->createTable(entity);
}

qint8 EntityManager::count(const QSharedPointer<Entity> &entity, bool ignoreID) {
    qint8 rc = -1;
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->count(entity, ignoreID);
    this->db->select(q);
    if (q.next()) {
        rc = q.value(0).toInt();
    }
    return rc;
}

qint8 EntityManager::count(const QString &tableName) {
    qint8 rc = -1;
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->count(tableName);
    this->db->select(q);
    if (q.next()) {
        rc = q.value(0).toInt();
    }
    return rc;
}

void EntityManager::setConnectionNames(QStringList list) {
    EntityManager::connectionNames = list;
}
