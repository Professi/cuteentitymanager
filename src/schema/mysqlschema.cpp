//#include "mysqlschema.h"
//#include <QSqlQuery>
//using namespace CuteEntityManager;

//MysqlSchema::MysqlSchema(std::shared_ptr<Database> database) : Schema(database) {

//}

//MysqlSchema::~MysqlSchema() {

//}

//QHash<QString, QString> *MysqlSchema::getTypeMap() {
//    if (this->typeMap.data()->empty()) {
//        this->typeMap.data()->insert(TYPE_SMALLINT, "tinyint");
//        this->typeMap.data()->insert(TYPE_BOOLEAN, "boolean");
//        this->typeMap.data()->insert(TYPE_SMALLINT, "smallint");
//        this->typeMap.data()->insert(TYPE_INTEGER, "int");
//        this->typeMap.data()->insert(TYPE_BIGINT, "bigint");
//        this->typeMap.data()->insert(TYPE_FLOAT, "float");
//        this->typeMap.data()->insert(TYPE_DOUBLE, "double");
//        this->typeMap.data()->insert(TYPE_FLOAT, "real");
//        this->typeMap.data()->insert(TYPE_DECIMAL, "decimal");
//        this->typeMap.data()->insert(TYPE_TEXT, "text");
//        this->typeMap.data()->insert(TYPE_STRING, "varchar");
//        this->typeMap.data()->insert(TYPE_CHAR, "char");
//        this->typeMap.data()->insert(TYPE_BINARY, "blob");
//        this->typeMap.data()->insert(TYPE_DATETIME, "datetime");
//        this->typeMap.data()->insert(TYPE_DATE, "date");
//        this->typeMap.data()->insert(TYPE_TIME, "time");
//        this->typeMap.data()->insert(TYPE_TIMESTAMP, "timestamp");
//    }
//    return this->typeMap.data();
//}

////QString Database::mysqlTableList() {
////    return "SHOW TABLES;";
////}
