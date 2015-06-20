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
#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H
#include <QString>
#include <QHash>
#include <QSharedPointer>
#include <QPointer>
#include <QSqlQuery>
#include "relation.h"
namespace CuteEntityManager {
class Schema;
class Entity;
class Database;
/**
  RESTRICT, CASCADE, NO ACTION, SET DEFAULT, SET NULL
*/
enum DbForeignKeyCascade {
    RESTRICT,
    CASCADE,
    NO_ACTION,
    SET_DEFAULT,
    SET_NULL,
};

class QueryBuilder {
  public:
    QueryBuilder(QSharedPointer<Schema> schema, QSharedPointer<Database> database);
    virtual ~QueryBuilder();
    virtual bool createTable(const QSharedPointer<Entity> &entity) const;
    virtual bool createIndices(const QSharedPointer<Entity> &entity) const;
    virtual QString createTable(const QString &tableName,
                                const QHash<QString, QString> &tableDefinition) const;
    virtual QString createTableQuery(const QString &tableName,
                                     const QHash<QString, QString> &tableDefinition) const;
    virtual QString renameTable(QString tableName, QString newName) const;
    virtual QString dropTable(QString tableName) const;
    virtual QString truncateTable(QString tableName) const;
    virtual QString addColumn(QString tableName, QString columnName,
                              QString columnType) const;
    virtual QString dropColumn(QString tableName, QString columName)const;
    virtual QString renameColumn(QString tableName, QString oldName,
                                 QString newName) const;
    virtual QString alterColumn(QString tableName, QString columnName,
                                QString newType)const;
    virtual QString addPrimaryKey(QString name, QString tableName,
                                  QStringList columns)const;
    virtual QString dropPrimaryKey(QString name, QString tableName) const;
    virtual QString addForeignKey(QString name, QString tableName,
                                  QStringList columns,
                                  QString refTableName,
                                  QStringList refColumns, QString deleteConstraint,
                                  QString updateConstraint) const;
    QString generateIndexName(const QString &name, const QString &table,
                              const QString &refColumn, const QString &refTable, const bool fk) const;
    QString generateColumnNameID(QString name) const;
    virtual QString getForeignKeyCascade(DbForeignKeyCascade cascade) const;
    virtual QString dropForeignKey(QString name, QString tableName) const;
    virtual QString createIndex(QString name, QString tableName,
                                QStringList columns,
                                bool unique)const;
    virtual QString dropIndex(QString name, QString tableName)const;
    virtual QString createFkSuperClass(const Entity *e) const;
    QHash<QString, QVariant> getEntityAttributes(const QHash<QString, QMetaProperty>
            &props,
            const QSharedPointer<Entity> &entity) const;
    virtual QStringList relationFks(const QSharedPointer<Entity> &entity) const;

    virtual QString createForeignKeyManyToMany(const QString &tableName,
            const QSharedPointer<Entity> &entity, const QString &update,
            const QString &remove) const;

    QSharedPointer<Schema> getSchema() const;
    void setSchema(const QSharedPointer<Schema> &value);

    QSharedPointer<Database> getDatabase() const;
    void setDatabase(const QSharedPointer<Database> &value);
    QHash<QString, QHash<QString, QString>> generateRelationTables(
            const QSharedPointer<Entity> &entity)
                                         const;
    QHash<QString, QString> generateTableDefinition(const QSharedPointer<Entity>
            &entity)
    const;
    QString generateManyToManyTableName(const QSharedPointer<Entity> &firstEntity,
                                        const QSharedPointer<Entity> &secondEntity) const;

    QString transformTypeToAbstractDbType(QString typeName) const;
    QString transformAbstractTypeToRealDbType(QString typeName) const;
    QString getColumnType(const QString &type) const;
    QSqlQuery find(const qint64 &id, const QString &tableName) const;
    QSqlQuery findByAttributes(const QHash<QString, QVariant> &m,
                               const QString &tableName,
                               const bool &ignoreID = true, const qint64 limit = 0,
                               const qint64 offset = 0) const;
    QSqlQuery findByAttributes(const QSharedPointer<Entity> &e,
                               bool ignoreID = true,
                               const qint64 limit = 0, const qint64 offset = 0);
    QSqlQuery findAll(const QString &tableName) const;
    QSqlQuery remove(const QSharedPointer<Entity> &entity) const;
    QSqlQuery findId(const QSharedPointer<Entity> &entity) const;
    QSqlQuery count(const QSharedPointer<Entity> &entity, bool ignoreID) const;
    QSqlQuery count(const QString &tableName) const;
    QSqlQuery merge(const QSharedPointer<Entity> &entity) const;
    QSqlQuery create(const QSharedPointer<Entity> &entity) const;
    QSqlQuery oneToMany(const QString &tableName, const QString &attribute,
                        const qint64 &id,
                        const qint64 &limit = 0);
    QSqlQuery manyToMany(const QString &tableName, const QString &attribute,
                         const qint64 &id,
                         const QString &foreignKey,
                         const QString &foreignTable);
    QSqlQuery manyToManyDelete(const QString &tableName, const QString &attribute,
                               const qint64 &id);
    QSqlQuery manyToManyInsert(const QString &tableName, const QString &col1,
                               const QString &col2) const;

    virtual QString limit(const qint64 &limit, const qint64 &offset) const;
    QString generateManyToManyColumnName(const QSharedPointer<Entity> &entity)
    const;
    QSqlQuery getQuery() const;

  protected:
    virtual void createRelationFK(QStringList &queries, const QSharedPointer<Entity> &entity, const Relation &relation, const QMetaProperty &metaProperty, const QString &update, const QString &remove) const;
    void insertRelationId(const Entity *e, QHash<QString, QVariant> &map,
                          QString relName) const;
    QString buildColumns(const QStringList &columns) const;
    QHash<QString, QVariant> getManyToOneAttributes(const
            QHash<QString, QMetaProperty>
            &props,
            const QSharedPointer<Entity> &entity) const;
    QHash<QString, QMetaProperty> getMetaProperties(const QSharedPointer<Entity>
            &entity)
    const;
    QHash<QString, QVariant> getPropertyValues(const QHash<QString, QMetaProperty>
            &metaProps,
            const QSharedPointer<Entity> &entity) const;
    QString buildCreateQuery(QHash<QString, QVariant>::const_iterator i,
                             QHash<QString, QVariant>::const_iterator end,
                             QString &p1, QString &p2) const;
    void bindValues(const QHash<QString, QVariant> &h, QSqlQuery &q,
                    bool ignoreID = false) const;
    QString where(const QSharedPointer<Entity> &entity, QString conjunction = ",",
                  bool ignoreID = false) const;
    QString where(const QHash<QString, QVariant> &m,
                  const QString &conjunction = ",",
                  bool ignoreID = false) const;
    QString attributes(const QHash<QString, QVariant> &m,
                       const QString &conjunction = ",",
                       bool ignoreID = false) const;
    QHash<QString, QVariant> saveAttributes(const QSharedPointer<Entity> &entity)
    const;
    QString leftJoin(const QString &foreignTable, const QString &tableName,
                     const QString &foreignKey);
    QString superClassColumnName(const QMetaObject *&superMeta) const;

    QSharedPointer<Schema> schema;
    QSharedPointer<Database> database;
};
}

#endif // QUERYBUILDER_H
