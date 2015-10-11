#include "mysqlquerybuilder.h"
#include "../schema.h"

CuteEntityManager::MysqlQueryBuilder::MysqlQueryBuilder(
    CuteEntityManager::Schema *schema,
    QSharedPointer<CuteEntityManager::Database> database)  :
    CuteEntityManager::QueryBuilder(schema,
                                    database) {

}

QString CuteEntityManager::MysqlQueryBuilder::renameColumn(QString tableName,
        QString oldName, QString newName) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " CHANGE " +
           this->schema->quoteColumnName(oldName) + " " +
           this->schema->quoteColumnName(
               newName);
    /**
      * @todo must append datatype
      */
}

QString CuteEntityManager::MysqlQueryBuilder::createIndex(QString name,
        QString tableName, QStringList columns, bool unique) const {
    QString s = "ALTER TABLE ";
    s += this->schema->quoteTableName(tableName);
    s += (unique ? "ADD UNIQUE INDEX " : "ADD INDEX ") +
         this->schema->quoteTableName(
             name) + " (";
    s.append(this->buildColumns(columns));
    s.append(");");
    return s;
}

QString CuteEntityManager::MysqlQueryBuilder::dropForeignKey(QString name,
        QString tableName) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " DROP FOREIGN KEY " +
           this->schema->quoteColumnName(name);
}

QString CuteEntityManager::MysqlQueryBuilder::limit(const quint64 &limit,
        const quint64 &offset, bool withSpace) const {
    QString s = "";
    if (limit > 0) {
        s.append((withSpace ? " " : "") + this->limitKeyword() + " " +
                 QString::number(limit));
        if (offset > 0) {
            s.append(" " + this->offsetKeyword() + QString::number(offset));
        }
    } else if (offset > 0) {
        s.append((withSpace ? " " : "") + this->limitKeyword() + " " +
                 QString::number(offset) + ", 18446744073709551615"); //2^64-1
    }
    return s;
}
