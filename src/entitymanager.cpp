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
using namespace CuteEntityManager;
/**
 * Relationen fehlen noch
 * Fehlermeldungen erstellen am besten eine Exception Klasse diesbzgl. erstellen
 */

QStringList EntityManager::connectionNames = QStringList();

void EntityManager::init() {
    auto schema = CuteEntityManager::getSchema(CuteEntityManager::getDatabaseType(
                      this->db.data()->getDatabase().driverName()), this->db);
    this->schema = QSharedPointer<Schema>(schema);
    this->schema.data()->setTables(this->schema.data()->getTableSchemas());
}

EntityManager::EntityManager(QSqlDatabase database) {
    auto db = new Database(database);
    this->db = QSharedPointer<Database>(db);
    this->init();
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

bool EntityManager::create(QSharedPointer<Entity> &entity) {

}

EntityManager::~EntityManager() {
    EntityManager::removeConnectionName(this->db->getConnectionName());
}

QStringList EntityManager::getConnectionNames() {
    return EntityManager::connectionNames;
}

void EntityManager::bindValues(const QHash<QString, QVariant> &h, QSqlQuery &q, bool ignoreID) {
    QHash<QString, QVariant>::const_iterator i = h.constBegin();
    while (i != h.constEnd()) {
        if (!ignoreID || (ignoreID && !(i.key() == "id"))) {
            q.bindValue(":" + i.key(), i.value());
        }
        ++i;
    }
}

//qint8 EntityManager::count(Entity *entity, bool ignoreID) {
//    qint8 rc = 0;
//    QSqlQuery q = this->db->getQuery("SELECT COUNT(*) FROM " + entity->getTablename() + this->where(
//                                         entity->getAttributeValues(), "AND", ignoreID));
//    this->bindValues(entity->getAttributeValues(), q);
//    this->db->select(q);
//    if (q.next()) {
//        rc = q.value(0).toInt();
//    }
//    return rc;
//}

QString EntityManager::buildCreateQuery(QHash<QString, QVariant>::const_iterator i,
                                        QHash<QString, QVariant>::const_iterator end, QString &p1, QString &p2) {
    bool first = true;
    while (i != end) {
        if (!first) {
            p1 += ",";
            p2 += ",";
        } else {
            first = false;
        }
        p1 += i.key();
        p2 += ":" + i.key();
        ++i;
    }
    p1 += ")";
    p2 += ");";
    return p1 + p2;
}

//bool EntityManager::create(QSharedPointer<Entity> &entity) {
//    bool rc = false;
//    if (this->checkTable(entity) && this->count(entity) == 0) {
//        QSqlQuery q = this->db->getQuery();
//        QString p1 = "INSERT INTO " + entity->getTablename() + "(";
//        QString p2 = "VALUES(";
//        entity->setId(this->db->getLastId());
//        if (!entity->getAttributeValues()->isEmpty()) {
//            q.prepare(this->buildCreateQuery(entity->getAttributeValues()->constBegin(), entity->getAttributeValues()->constEnd(),
//                                             p1, p2));
//        }
//        this->bindValues(entity->getAttributeValues(), q);
//    }
//    return rc;
//}

QHash<QString, QVariant> EntityManager::find(qint64 id, QString tblname) {
    QSqlQuery q = this->db->getQuery("SELECT * FROM " + tblname + " WHERE id= :id LIMIT 1;");
    q.bindValue(":id", id);
    this->db->select(q);
    QSqlRecord rec = q.record();
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    if (q.next()) {
        for (int var = 0; var < rec.count(); ++var) {
            map.insert(rec.fieldName(var), q.value(rec.indexOf(rec.fieldName(
                    var)))); // parameters of q.value can maybe replaced with var
        }
    }
    return map;
}

QList<QHash <QString, QVariant> > EntityManager::findByAttributes(const QHash<QString, QVariant> &m,
        const QString &tblname,
        bool ignoreID) {
    QSqlQuery q = this->db->getQuery("SELECT * FROM " + tblname + this->where(m, "AND", ignoreID));
    this->bindValues(m, q, true);
    return this->convertQueryResult(q);
}

bool EntityManager::merge(QSharedPointer<Entity> &entity) {

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
    QSqlQuery q = this->db->getQuery("SELECT * FROM " + tblname + ";");
    return this->convertQueryResult(q);
}

//bool EntityManager::merge(Entity *entity) {
//    if (this->count(entity) == 0 && entity->getId() != -1) {
//        QSqlQuery q = this->db->getQuery("UPDATE " + entity->getTablename() + " SET " + this->attributes(
//                                             entity->getAttributeValues()) + " WHERE id=:idM;");
//        this->bindValues(entity->getAttributeValues(), q);
//        q.bindValue(":idM", entity->getId());
//        return this->db->transaction(q);
//    } else {
//        return false;
//    }
//}


//qint64 EntityManager::findId(Entity *entity) {
//    qint64 r = -1;
//    QSqlQuery q = this->db->getQuery("SELECT id FROM " + entity->getTablename() + this->where(entity->getAttributeValues(),
//                                     "AND", true) + " LIMIT 1");
//    this->bindValues(entity->getAttributeValues(), q);
//    this->db->select(q);
//    if (q.next()) {
//        r = q.value(0).toInt();
//    }
//    return r;
//}

QString EntityManager::attributes(const QHash<QString, QVariant> &m, const QString &conjunction, bool ignoreID) {
    QString rc = "";
    if (!m.isEmpty()) {
        QHash<QString, QVariant>::const_iterator i = m.constBegin();
        while (i != m.constEnd()) {
            if (!ignoreID || (ignoreID && !(i.key() == "id"))) {
                if (!(rc == "")) {
                    rc += " " + conjunction + " ";
                }
                rc += i.key() + "= :" + i.key();
            }
            ++i;
        }
    }
    return rc;
}


QString EntityManager::where(const QHash<QString, QVariant> &m, const QString &conjunction, bool ignoreID) {
    if (m.size() == 0 || (ignoreID && m.contains("id") && m.size() == 1)) {
        return "";
    }
    return " WHERE " + this->attributes(m, conjunction, ignoreID);
}

//QString EntityManager::where(Entity *entity, QString conjunction, bool ignoreID) {
//    return this->where(entity->getAttributeValues(), conjunction, ignoreID);
//}

//QList<QHash <QString, QVariant> > EntityManager::findByAttributes(Entity *entity, bool ignoreID) {
//    return this->findByAttributes(entity->getAttributeValues(), entity->getTablename(), ignoreID);
//}

bool EntityManager::save(QSharedPointer<Entity> &entity) {
    if (entity.data()->getId() > -1) {
        return this->merge(entity);
    } else {
        return this->create(entity);
    }
}


bool EntityManager::remove(QSharedPointer<Entity> &entity) {
    bool rc = false;
    QSqlQuery q = this->db->getQuery("DELETE FROM " + entity.data()->getTablename() + " WHERE id= :id;");
    q.bindValue(":id", entity.data()->getId());
    if (this->db->transaction(q)) {
        entity.clear();
        rc = true;
    }
    return rc;
}

void EntityManager::setConnectionNames(QStringList list) {
    EntityManager::connectionNames = list;
}
