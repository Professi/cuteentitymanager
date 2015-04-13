#include "sqliteschema.h"
#include "../database.h"
#include <QSqlRecord>
#include <QSqlResult>
#include "sqlitequerybuilder.h"
using namespace CuteEntityManager;

SqliteSchema::SqliteSchema(QSharedPointer<Database> database) : Schema(database) {
    this->queryBuilder = QSharedPointer<QueryBuilder>(new SqliteQueryBuilder(QSharedPointer<Schema>(this), database));
}

SqliteSchema::~SqliteSchema() {

}

QSharedPointer<QHash<QString, QString>> SqliteSchema::getTypeMap() {
    if (this->typeMap.data()->empty()) {
        this->typeMap.data()->insert(TYPE_PK, "integer PRIMARY KEY AUTOINCREMENT NOT NULL");
        this->typeMap.data()->insert(TYPE_BIGPK, "integer PRIMARY KEY AUTOINCREMENT NOT NULL");
        this->typeMap.data()->insert(TYPE_BOOLEAN, "boolean");
        this->typeMap.data()->insert(TYPE_SMALLINT, "smallint");
        this->typeMap.data()->insert(TYPE_INTEGER, "integer");
        this->typeMap.data()->insert(TYPE_BIGINT, "bigint");
        this->typeMap.data()->insert(TYPE_FLOAT, "float");
        this->typeMap.data()->insert(TYPE_DOUBLE, "double");
        this->typeMap.data()->insert(TYPE_FLOAT, "real");
        this->typeMap.data()->insert(TYPE_DECIMAL, "decimal(10,0)");
        this->typeMap.data()->insert(TYPE_TEXT, "text");
        this->typeMap.data()->insert(TYPE_STRING, "text");
        this->typeMap.data()->insert(TYPE_CHAR, "char");
        this->typeMap.data()->insert(TYPE_BINARY, "blob");
        this->typeMap.data()->insert(TYPE_DATETIME, "datetime");
        this->typeMap.data()->insert(TYPE_DATE, "date");
        this->typeMap.data()->insert(TYPE_TIME, "time");
        this->typeMap.data()->insert(TYPE_TIMESTAMP, "timestamp");
        this->typeMap.data()->insert(TYPE_MONEY, "decimal(19,4)");
    }
    return this->typeMap;
}

QStringList SqliteSchema::findTableNames(QString schema) {
    auto l = QStringList();
    QString sql = "SELECT DISTINCT tbl_name FROM sqlite_master WHERE tbl_name<>'sqlite_sequence' ORDER BY tbl_name";
    auto q = this->database.data()->getQuery();
    q.prepare(sql);
    this->database.data()->select(q);
    while (q.next()) {
        l.append(q.value(0).toString());
    }
    return l;
}

QHash<QString, QStringList> SqliteSchema::findUniqueIndexes(const QSharedPointer<TableSchema> &table) {
    QHash<QString, QStringList> uniqueIndexes = QHash<QString, QStringList>();
    QSqlQuery q = this->database.data()->getQuery();
    q.setForwardOnly(true);
    q.exec("PRAGMA index_list(" + this->quoteSimpleTableName(table->getName()) + ')');
    while (q.next()) {
        QString indexName = q.value("name").toString();
        QSqlQuery q2 = this->database.data()->getQuery();
        q2.setForwardOnly(true);
        if (q.value("unique").toBool()) {
            q2.exec("PRAGMA index_info(" + this->quoteSimpleTableName(indexName) + ")");
            QStringList indexInfo = QStringList();
            while (q2.next()) {
                indexInfo.append(q2.value("name").toString());
            }
            uniqueIndexes.insert(indexName, indexInfo);
        }
    }
    return uniqueIndexes;
}

void SqliteSchema::findConstraints(const QSharedPointer<TableSchema> &ts) {
    QSqlQuery q = this->database.data()->getQuery();
    q.setForwardOnly(true);
    q.exec("PRAGMA foreign_key_list(" + this->quoteSimpleTableName(ts.data()->getName()) + ')');
    auto foreignKeys = ts.data()->getRelations();
    while (q.next()) {
        bool ok;
        int id = q.value("id").toInt(&ok);
        if (ok) {
            auto rel = new QSqlRelation(q.value("table").toString(), q.value("from").toString(), q.value("to").toString());
            auto ptr = QSharedPointer<QSqlRelation>(rel);
            foreignKeys.insert(QString::number(id), ptr);
        }
    }
    ts.data()->setRelations(foreignKeys);
}

bool SqliteSchema::findColumns(const QSharedPointer<TableSchema> &ts) {
    QSqlQuery q = this->database.data()->getQuery();
    q.setForwardOnly(true);
    q.exec("SELECT * FROM " + this->quoteSimpleTableName(ts.data()->getName()) + " LIMIT 0");
    QHash<QString, QSharedPointer<QSqlField>> columns = QHash<QString, QSharedPointer<QSqlField>>();
    auto rec = q.record();
    int count = rec.count();
    if (count == 0) {
        return false;
    }
    for (int var = 0; var < count; ++var) {
        QSqlField f = rec.field(var);
        columns.insert(f.name(), QSharedPointer<QSqlField>(new QSqlField(f)));
    }
    ts.data()->setColumns(columns);
    return true;
}

QSharedPointer<TableSchema> SqliteSchema::loadTableSchema(QString name) {
    auto table = new TableSchema();
    auto ptr = QSharedPointer<TableSchema>(table);
    table->setName(name);
    table->setFullName(name);
    if (this->findColumns(ptr)) {
        this->findConstraints(ptr);
    } else {
        ptr.clear();
    }
    return ptr;
}
