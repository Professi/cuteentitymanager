#include "pgsqlschema.h"
using namespace CuteEntityManager;

PgSqlSchema::PgSqlSchema(std::shared_ptr<Database> database) : Schema(database) {

}

PgSqlSchema::~PgSqlSchema() {

}

QHash<QString, QString> *PgSqlSchema::getTypeMap() {
    if (this->typeMap.data()->empty()) {
//        this->typeMap->data()->insert(TYPE_SMALLINT, 'tinyint');
//        this->typeMap->data()->insert(TYPE_SMALLINT, 'bit');
//        this->typeMap->data()->insert(TYPE_BOOLEAN, 'boolean');
//        this->typeMap->data()->insert(TYPE_BOOLEAN, 'bool');
//        this->typeMap->data()->insert(TYPE_SMALLINT, 'smallint');
//        this->typeMap->data()->insert(TYPE_INTEGER, 'mediumint');
//        this->typeMap->data()->insert(TYPE_INTEGER, 'int');
//        this->typeMap->data()->insert(TYPE_INTEGER, 'integer');
//        this->typeMap->data()->insert(TYPE_BIGINT, 'bigint');
//        this->typeMap->data()->insert(TYPE_FLOAT, 'float');
//        this->typeMap->data()->insert(TYPE_DOUBLE, 'double');
//        this->typeMap->data()->insert(TYPE_FLOAT, 'real');
//        this->typeMap->data()->insert(TYPE_DECIMAL, 'decimal');
//        this->typeMap->data()->insert(TYPE_DECIMAL, 'numeric');
//        this->typeMap->data()->insert(TYPE_TEXT, 'tinytext');
//        this->typeMap->data()->insert(TYPE_TEXT, 'mediumtext');
//        this->typeMap->data()->insert(TYPE_TEXT, 'longtext');
//        this->typeMap->data()->insert(TYPE_TEXT, 'text');
//        this->typeMap->data()->insert(TYPE_STRING, 'varchar');
//        this->typeMap->data()->insert(TYPE_STRING, 'string');
//        this->typeMap->data()->insert(TYPE_STRING, 'char');
//        this->typeMap->data()->insert(TYPE_BINARY, 'blob');
//        this->typeMap->data()->insert(TYPE_DATETIME, 'datetime');
//        this->typeMap->data()->insert(TYPE_DATE, 'year');
//        this->typeMap->data()->insert(TYPE_DATE, 'date');
//        this->typeMap->data()->insert(TYPE_TIME, 'time');
//        this->typeMap->data()->insert(TYPE_TIMESTAMP, 'timestamp');
//        this->typeMap->data()->insert(TYPE_STRING, 'enum');
    }
    return this->typeMap.data();
}

