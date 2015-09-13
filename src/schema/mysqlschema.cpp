#include "mysqlschema.h"
#include "../database.h"
#include <QSqlRecord>
#include <QSqlResult>
#include "mysqlquerybuilder.h"
using namespace CuteEntityManager;

MysqlSchema::MysqlSchema(QSharedPointer<Database> database) : Schema(
        database, QSharedPointer<QueryBuilder>(new MysqlQueryBuilder(
                    QSharedPointer<Schema>
                    (this), database))) {

}

QSharedPointer<QHash<QString, QString> > MysqlSchema::getTypeMap() {
    if (this->typeMap->empty()) {
        this->typeMap->insert(TYPE_PK,
                              "integer PRIMARY KEY AUTOINCREMENT NOT NULL");
        this->typeMap->insert(TYPE_BIGPK,
                              "bigint PRIMARY KEY AUTOINCREMENT NOT NULL");
        this->typeMap->insert(TYPE_BOOLEAN, "boolean");
        this->typeMap->insert(TYPE_SMALLINT, "smallint");
        this->typeMap->insert(TYPE_INTEGER, "integer");
        this->typeMap->insert(TYPE_BIGINT, "bigint");
        this->typeMap->insert(TYPE_FLOAT, "float");
        this->typeMap->insert(TYPE_DOUBLE, "double");
        this->typeMap->insert(TYPE_FLOAT, "real");
        this->typeMap->insert(TYPE_DECIMAL, "decimal(10,0)");
        this->typeMap->insert(TYPE_TEXT, "text");
        this->typeMap->insert(TYPE_STRING, "text");
        this->typeMap->insert(TYPE_CHAR, "char");
        this->typeMap->insert(TYPE_BINARY, "blob");
        this->typeMap->insert(TYPE_DATETIME, "datetime");
        this->typeMap->insert(TYPE_DATE, "date");
        this->typeMap->insert(TYPE_TIME, "time");
        this->typeMap->insert(TYPE_TIMESTAMP, "timestamp");
        this->typeMap->insert(TYPE_MONEY, "decimal(19,4)");
    }
    return this->typeMap;
}

QStringList MysqlSchema::findTableNames(QString schema) {
    QString sql = "SHOW TABLES";
    if (!schema.isEmpty()) {
        sql +=  " FROM " + this->quoteSimpleTableName(schema);
    }
    auto l = QStringList();
    auto q = this->database->getQuery();
    q.prepare(sql);
    this->database->select(q);
    while (q.next()) {
        l.append(q.value(0).toString());
    }
    return l;
}

QHash<QString, QStringList> MysqlSchema::findUniqueIndexes(
    const QSharedPointer<TableSchema> &table) {
    QHash<QString, QStringList> uniqueIndexes = QHash<QString, QStringList>();
    QSqlQuery q = this->database->getQuery();
    q.setForwardOnly(true);
    q.exec("SHOW INDEX FROM " + this->quoteSimpleTableName(
               table->getName()));
    while (q.next()) {
        QString indexName = q.value("Key_name").toString();
        if (!(q.value("Non_unique").toBool())) {
            QStringList indexInfo = QStringList();
            indexInfo.append(q.value("Column_name").toString());
            uniqueIndexes.insert(indexName, indexInfo);
        }
    }
    return uniqueIndexes;
}

void MysqlSchema::findConstraints(const QSharedPointer<TableSchema> &ts) {
    QString sql =
        "SELECT " + this->quoteColumnName("table_name") + ", " +
        this->quoteColumnName("column_name") + ", " +
        this->quoteColumnName("referenced_table_name") + ", " +
        this->quoteColumnName("referenced_column_name");
    sql +=  " FROM " + this->quoteTableName("information_schema.key_column_usage");
    sql += "WHERE " + this->quoteColumnName("referenced_table_name") +
           " is not null";
    sql += " AND " + this->quoteColumnName("table_schema") + " = ?";
    sql += " AND " + this->quoteColumnName("table_name") + " = ?";
    QSqlQuery q = this->database->getQuery();
    q.prepare(sql);
    q.bindValue(0, this->getDatabase()->getDatabase().databaseName());
    q.bindValue(1, ts->getName());
    this->database->select(q);
    auto foreignKeys = ts->getRelations();
    int id = 0;
    while (q.next()) {
        auto rel = new QSqlRelation(q.value("referenced_table_name").toString(),
                                    q.value("column_name").toString(),
                                    q.value("referenced_column_name").toString());
        auto ptr = QSharedPointer<QSqlRelation>(rel);
        foreignKeys.insert(QString::number(id), ptr);
        ++id;
    }
    ts->setRelations(foreignKeys);
}

QSharedPointer<TableSchema> MysqlSchema::loadTableSchema(QString name) {
    auto ptr = QSharedPointer<TableSchema>(new TableSchema());
    this->resolveTableNames(ptr, name);
    if (this->findColumns(ptr)) {
        this->findConstraints(ptr);
    } else {
        ptr.clear();
    }
    return ptr;
}

void MysqlSchema::resolveTableNames(const QSharedPointer<TableSchema> &ts,
                                    QString name) {
    QStringList parts = name.replace("`", "").split(".");
    if (parts.size() > 1) {
        ts->setSchemaName(parts.at(0));
        ts->setName(parts.at(1));
        ts->setFullName(ts->getSchemaName() + "." + ts->getName());
    } else {
        ts->setFullName(parts.at(0));
        ts->setName(parts.at(0));
    }
}
