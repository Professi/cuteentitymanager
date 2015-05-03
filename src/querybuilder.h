#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
#include <QString>
#include <QHash>
#include <QSharedPointer>
#include <QPointer>
#include <QSqlQuery>
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
            const QSharedPointer<Entity> &entity) const;

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
    QSqlQuery find(const qint64 &id, const QString &tableName) const;
    QSqlQuery findByAttributes(const QHash<QString, QVariant> &m, const QString &tableName, const bool &ignoreID) const;
    QSqlQuery findByAttributes(const QSharedPointer<Entity> &e,bool ignoreID = true);
    QSqlQuery findAll(const QString &tableName) const;
    QSqlQuery remove(const QSharedPointer<Entity> &entity) const;
    QSqlQuery findId(const QSharedPointer<Entity> &entity) const;
    QSqlQuery count(const QSharedPointer<Entity> &entity, bool ignoreID) const;
    QSqlQuery count(const QString &tableName) const;
    QSqlQuery merge(const QSharedPointer<Entity> &entity) const;
    QSqlQuery create(const QSharedPointer<Entity> &entity) const;
    virtual QString limit(const qint8 limit, const qint64 offset) const;

  protected:
    void insertRelationId(const Entity *e, QHash<QString, QVariant> &map, QString relName) const;
    QString buildColumns(const QStringList &columns) const;
    QHash<QString, QVariant> getManyToOneAttributes(const QHash<QString, QMetaProperty> &props,
            const QSharedPointer<Entity> &entity) const;
    QHash<QString, QMetaProperty> getMetaProperties(const QSharedPointer<Entity> &entity) const;
    QHash<QString, QVariant> getPropertyValues(const QHash<QString, QMetaProperty> &metaProps,
            const QSharedPointer<Entity> &entity) const;
    QString buildCreateQuery(QHash<QString, QVariant>::const_iterator i, QHash<QString, QVariant>::const_iterator end,
                             QString &p1, QString &p2) const;
    void bindValues(const QHash<QString, QVariant> &h, QSqlQuery &q, bool ignoreID = false) const;
    QString where(const QSharedPointer<Entity> &entity, QString conjunction = ",", bool ignoreID = false) const;
    QString where(const QHash<QString, QVariant> &m, const QString &conjunction = ",", bool ignoreID = false) const;
    QString attributes(const QHash<QString, QVariant> &m, const QString &conjunction = ",", bool ignoreID = false) const;
    QHash<QString, QVariant> saveAttributes(const QSharedPointer<Entity> &entity) const;

    QSharedPointer<Schema> schema;
    QSharedPointer<Database> database;
};
}

#endif // QUERYBUILDER_H