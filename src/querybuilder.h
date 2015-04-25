#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
#include <QString>
#include <QHash>
#include <QSharedPointer>
#include <QPointer>
namespace CuteEntityManager {
class Schema;
class Entity;
class Database;
class QueryBuilder {
  public:
    QueryBuilder(QSharedPointer<Schema> schema, QSharedPointer<Database> database);
    virtual ~QueryBuilder();
    virtual bool createTable(const QSharedPointer<Entity> &entity) const;
    virtual bool createTable(const QString &tableName, const QHash<QString, QString> &tableDefinition) const;
    virtual QString createTableQuery(const QString &tableName, const QHash<QString, QString> &tableDefinition) const;
    virtual QString renameTable(QString tableName, QString newName) const;
    virtual QString dropTable(QString tableName) const;
    virtual QString truncateTable(QString tableName) const;
    virtual QString addColumn(QString tableName, QString columnName, QString columnType) const;
    virtual QString dropColumn(QString tableName, QString columName)const;
    virtual QString renameColumn(QString tableName, QString oldName, QString newName) const;
    virtual QString alterColumn(QString tableName, QString columnName, QString newType)const;
    virtual QString addPrimaryKey(QString name, QString tableName, QStringList columns)const;
    virtual QString dropPrimaryKey(QString name, QString tableName) const;
    virtual QString addForeignKey(QString name, QString tableName, QStringList columns, QString refTableName,
                                  QStringList refColumns, QString deleteConstraint, QString updateConstraint) const;
    virtual QString dropForeignKey(QString name, QString tableName) const;
    virtual QString createIndex(QString name, QString tableName, QStringList columns, bool unique)const;
    virtual QString dropIndex(QString name, QString tableName)const;
    QHash<QString, QVariant> getEntityAttributes(const QHash<QString, QMetaProperty> &props,
            const QSharedPointer<Entity> &entity);

    QSharedPointer<Schema> getSchema() const;
    void setSchema(const QSharedPointer<Schema> &value);

    QSharedPointer<Database> getDatabase() const;
    void setDatabase(const QSharedPointer<Database> &value);
    QHash<QString, QHash<QString, QString>> generateRelationTables(const QSharedPointer<Entity> &entity) const;
    QHash<QString, QString> generateTableDefinition(const QSharedPointer<Entity> &entity) const;
    QString generateManyToManyTableName(const QSharedPointer<Entity> &firstEntity,
                                        const QSharedPointer<Entity> &secondEntity) const;

    QString transformTypeToAbstractDbType(QString typeName) const;
    QString transformAbstractTypeToRealDbType(QString typeName) const;
    QString getColumnType(const QString &type) const;


  protected:
    void insertRelationId(const Entity *e, QHash<QString, QVariant> &map, QString relName);
    QString buildColumns(const QStringList &columns) const;
    QHash<QString, QVariant> getManyToOneAttributes(const QHash<QString, QMetaProperty> &props,
            const QSharedPointer<Entity> &entity);

    QSharedPointer<Schema> schema;
    QSharedPointer<Database> database;
};
}

#endif // QUERYBUILDER_H
