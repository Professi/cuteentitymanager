#ifndef MYSQLQUERYBUILDER_H
#define MYSQLQUERYBUILDER_H
#include "../querybuilder.h"
namespace CuteEntityManager {
class MysqlQueryBuilder : public QueryBuilder
{
public:
    MysqlQueryBuilder(QSharedPointer<Schema> schema,
                       QSharedPointer<Database> database);


    QString renameColumn(QString tableName, QString oldName,
                                 QString newName) const override;
    QString createIndex(QString name, QString tableName,
                                QStringList columns,
                                bool unique)const override;
        QString dropForeignKey(QString name, QString tableName) const override;


protected:
    QString limit(const quint64 &limit, const quint64 &offset,
                          bool withSpace = true) const override;
};

}
#endif // MYSQLQUERYBUILDER_H
