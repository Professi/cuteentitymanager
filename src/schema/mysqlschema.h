#ifndef MYSQLSCHEMA_H
#define MYSQLSCHEMA_H
#include "../schema.h"
namespace CuteEntityManager {
class TableSchema;
class MysqlSchema : public Schema {
  public:
    MysqlSchema(QSharedPointer<Database> database);
    QSharedPointer<QHash<QString, QString> > getTypeMap() override;

protected:
    QStringList findTableNames(QString schema = "") override;
    QHash<QString, QStringList> findUniqueIndexes(const
            QSharedPointer<TableSchema>
            &table) override;
    void findConstraints(const QSharedPointer<TableSchema> &ts) override;
    QSharedPointer<TableSchema> loadTableSchema(QString name)  override;
    void resolveTableNames(const QSharedPointer<TableSchema> &ts, QString name);

};
}

#endif // MYSQLSCHEMA_H
