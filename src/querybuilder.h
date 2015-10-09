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
#include <QStringList>
#include <QMetaProperty>
#include "relation.h"
#include "expression.h"
#include "query.h"
namespace CuteEntityManager {
class Schema;
class Entity;
class Database;
class Logger;
enum DbForeignKeyCascade {
    RESTRICT,
    CASCADE,
    NO_ACTION,
    SET_DEFAULT,
    SET_NULL,
};

class QueryBuilder {
    /**
     * EntityManager is a friend class, cause we want a light public api.
     */
    friend class EntityManager;
    friend class QueryInterpreter;
  public:
    QueryBuilder(QSharedPointer<Schema> schema, QSharedPointer<Database> database);
    virtual ~QueryBuilder();
    virtual bool createTable(const QSharedPointer<Entity> &entity,
                             bool createRelationTables = true) const;
    virtual bool createIndices(const QSharedPointer<Entity> &entity) const;
    virtual QString createTable(const QString &tableName,
                                const QHash<QString, QString> &tableDefinition) const;
    virtual bool createRelationTables(const QSharedPointer<Entity> &entity) const;
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
    virtual QString getForeignKeyCascade(DbForeignKeyCascade cascade) const;
    virtual QString dropForeignKey(QString name, QString tableName) const;
    virtual QString createIndex(QString name, QString tableName,
                                QStringList columns,
                                bool unique)const;
    virtual QString dropIndex(QString name, QString tableName)const;
    virtual QString createFkSuperClass(const Entity *e) const;
    virtual QStringList relationFks(const QSharedPointer<Entity> &entity) const;
    virtual bool supportsForeignKeys() const;

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
    QSqlQuery getQuery() const;
    QString transformTypeToAbstractDbType(QString typeName) const;
    QString transformAbstractTypeToRealDbType(QString typeName) const;
    QString getColumnType(const QString &type) const;
    virtual QString placeHolder(const QString &key) const;
    void bindValues(const QHash<QString, QVariant> &h, QSqlQuery &q,
                    bool ignoreID = false, const QString &primaryKey = QStringLiteral("id")) const;
    void bindValue(const QString &key, const QVariant &value, QSqlQuery &q) const;
    Expression where(QString column, QVariant value);
    Join joinClasses(const QSharedPointer<Entity> &mainEntity,
                     const QSharedPointer<Entity> &foreignEntity,
                     const QString &joinType = QStringLiteral("LEFT JOIN"))const;
    QList<Join> joinBaseClasses(const QSharedPointer<Entity> &entity);
    /**
     * @brief where
     * @param query
     * @param conditions
     * @param conjunction its AND or OR
     */
    Expression where(QHash<QString, QVariant> conditions,
                     QString conjunction = QStringLiteral("AND")) const;
    Expression where(QString condition,
                     QHash<QString, QVariant> values = QHash<QString, QVariant>()) const;
    //void where(Query &query,QHash<QString, QList<QVariant>> conditions, QString concat="AND");
    Expression between(QString column, QVariant firstValue,
                       QVariant secondValue) const;
    Expression notBetween(QString column, QVariant firstValue,
                          QVariant secondValue) const;
    Expression in(QString column, QList<QVariant> values) const;
    Expression notIn(QString column, QList<QVariant> values) const;
    Expression notOperator(QString op, QString column,
                           QVariant value) const;
    Expression orOperator(QHash<QString, QVariant> conditions,
                          bool like = false) const;
    Expression orOperator() const;
    Expression norOperator() const;
    Expression andOperator(QHash<QString, QVariant> conditions) const;
    Expression andOperator() const;
    Expression nandOperator() const;
    /**
     * @brief arbitraryOperator
     * @param query
     * @param op can be = | != | <> | > | < | >= | <= | !< | !> @see http://www.tutorialspoint.com/sql/sql-operators.htm comparison operators
     * @param column
     * @param value
     */
    Expression arbitraryOperator(QString op, QString column,
                                 QVariant value) const;
    Expression isNull(QString column) const;
    Expression isNotNull(QString column) const;

    Expression plainOr() const; //adds a simple OR to condition
    Expression plainNor() const;
    Expression plainAnd() const; //add a simple AND to condition
    Expression plainNand() const;
    /**
     * Generates 'foo' LIKE "%bar%"
     * @brief like
     * @param column
     * @param value
     */
    Expression like(QString column, QVariant value,
                    JokerPosition jp = JokerPosition::BOTH, QChar wildcard = '%');
    /**
     * @brief like
     * @param condition
     * @param concat
     */
    Expression like(QHash<QString, QVariant> conditions,
                    QString conjunction = QStringLiteral("AND"),
                    JokerPosition jp = JokerPosition::BOTH, QChar wildcard = '%');

  protected:
    class ClassAttributes {
      public:
        ClassAttributes() { }
        explicit ClassAttributes(const QString name,
                                 const QHash<QString, QVariant> attributes, QString pk = "id");
        QString getName() const;
        void setName(const QString &value);

        QHash<QString, QVariant> getAttributes() const;
        void setAttributes(const QHash<QString, QVariant> &value);

        QString getPk() const;
        void setPk(const QString &value);

      private:
        QString name;
        QString pk;
        QHash<QString, QVariant> attributes;
    };

    QStringList quoteTableNames(const QStringList &tables);
    QString getSeparator() const;
    void setSeparator(const QString &value);
    QSqlQuery find(const qint64 &id, const QString &tableName) const;
    QSqlQuery find(const qint64 &id, const QSharedPointer<Entity> &entity,
                   qint64 offset = 0, QString pk = "id") const;
    QSqlQuery findByAttributes(const QHash<QString, QVariant> &m,
                               const QString &tableName,
                               const bool &ignoreID = true, const qint64 limit = 0,
                               const qint64 offset = 0) const;
    QSqlQuery findByAttributes(const QSharedPointer<Entity> &e,
                               bool ignoreID = true,
                               const qint64 limit = 0, const qint64 offset = 0);
    QSqlQuery findAll(const QString &tableName) const;
    QSqlQuery findAll(const QSharedPointer<Entity> &entity, const qint64 limit = 0,
                      qint64 offset = 0);
    QList<QSqlQuery> remove(const QSharedPointer<Entity> &entity) const;
    QSqlQuery findId(const QSharedPointer<Entity> &entity) const;
    //QSqlQuery count(const QSharedPointer<Entity> &entity, bool ignoreID) const;
    QSqlQuery count(const QString &tableName) const;
    QList<QSqlQuery> merge(const QSharedPointer<Entity> &entity) const;
    QList<QSqlQuery> create(const QSharedPointer<Entity> &entity) const;
    QSqlQuery removeAll(const QString &tableName) const;
    QSqlQuery oneToMany(const QString &tableName, const QString &attribute,
                        const qint64 &id,
                        const qint64 &limit = 0);
    QSqlQuery manyToMany(const QString &tableName, const QString &attribute,
                         const qint64 &id);
    QSqlQuery manyToManyDelete(const QString &tableName, const QString &attribute,
                               const qint64 &id);
    QSqlQuery manyToManyInsert(const QString &tableName, const QString &col1,
                               const QString &col2) const;
    QSqlQuery remove(const QString &tableName, const qint64 &id,
                     const QString &primaryKey = "id") const;
    QSqlQuery insert(const QString &tableName, QHash<QString, QVariant> &attributes,
                     const QString &primaryKey = "id", bool withId = false) const;
    QSqlQuery update(const QString &tableName, QHash<QString, QVariant> &attributes,
                     const QString &primaryKey = "id") const;
    QList<QSqlQuery> createOrMerge(const QSharedPointer<Entity> &entity,
                                   bool insert) const;
    virtual QString limit(const quint64 &limit, const quint64 &offset,
                          bool withSpace = true) const;
    QString generateIndexName(const QString &name, const QString &table,
                              const QString &refColumn, const QString &refTable, const bool fk) const;
    QString generateColumnNameID(QString name) const;
    QString columnNameIDAppendix() const;
    virtual void createRelationFK(QStringList &queries,
                                  const QSharedPointer<Entity> &entity, const Relation &relation,
                                  const QMetaProperty &metaProperty, const QString &update,
                                  const QString &remove) const;
    void insertRelationId(const Entity *e, QHash<QString, QVariant> &map,
                          QString relName) const;
    QString buildColumns(const QStringList &columns) const;
    QHash<QString, QVariant> getManyToOneAttributes(QHash<QString, QMetaProperty>
            props,
            const QSharedPointer<Entity> &entity,
            QHash<QString, Relation> relations = QHash<QString, Relation>()) const;
    QHash<QString, QMetaProperty> getMetaProperties(const QSharedPointer<Entity>
            &entity)
    const;
    QHash<QString, QVariant> getPropertyValues(const QHash<QString, QMetaProperty>
            &metaProps,
            const QSharedPointer<Entity> &entity) const;
    QString generateManyToManyTableName(const QSharedPointer<Entity> &firstEntity,
                                        const QSharedPointer<Entity> &secondEntity, const Relation &r) const;
    QString generateManyToManyColumnName(const QSharedPointer<Entity> &entity)
    const;
    QString buildCreateQuery(QHash<QString, QVariant>::const_iterator i,
                             QHash<QString, QVariant>::const_iterator end,
                             QString &p1, QString &p2) const;
    QString where(const QSharedPointer<Entity> &entity, QString conjunction = ",",
                  bool ignoreID = false) const;
    QString where(const QHash<QString, QVariant> &m,
                  const QString &conjunction,
                  bool ignoreID = false, const QString &primaryKey = "id",
                  bool withKeyword = true) const;
    QString attributes(const QHash<QString, QVariant> &m, bool select = true,
                       const QString &conjunction = ",",
                       bool ignoreID = false, const QString &primaryKey = "id") const;
    QHash<QString, QVariant> saveAttributes(const QSharedPointer<Entity> &entity,
                                            QHash<QString, QMetaProperty> props = QHash<QString, QMetaProperty> (),
                                            QHash<QString, Relation> relations = QHash<QString, Relation>())
    const;
    QHash<QString, QMetaProperty> processProperties(const QSharedPointer<Entity> &e,
            QHash<QString, QMetaProperty> &usedProperties) const;
    QHash<QString, Relation> processRelations(const QSharedPointer<Entity> &e,
            QHash<QString, Relation> &usedRelations) const;
    QList<ClassAttributes> inheritedAttributes(
        const QSharedPointer<Entity> &entity) const;

    QString leftJoin(const QString &foreignTable, const QString &tableName,
                     const QString &foreignKey = "id", const QString &primaryKey = "id",
                     bool onlyCondition = false) const;
    QString superClassColumnName(const QMetaObject *&superMeta) const;
    QString addWildcard(QVariant var, JokerPosition jp,
                        QChar jokerChar = '%') const;

    QString joinSuperClasses(const QSharedPointer<Entity> &entity) const;
    virtual QString selectBase(const QStringList &tables,
                               const QStringList &columns = QStringList()) const;
    virtual QString countFunction(const QString &distinctColumn = "") const;
    virtual QString distinct() const;
    virtual QString notKeyword() const;
    virtual QString between() const;
    virtual QString andKeyword() const;
    virtual QString orKeyword() const;
    virtual QString inKeyword() const;
    virtual QString whereKeyword() const;
    virtual QString countKeyword() const;
    virtual Expression inFunction(QString column, QList<QVariant> values,
                                  bool notOp = false) const;
    virtual QString between(QString colName, QString valName1, QString valName2,
                            bool notOp = false) const;
    virtual QString likeKeyword() const;
    virtual QString limitKeyword() const;
    virtual QString offsetKeyword() const;
    QString appendNot(bool notOp) const;
    virtual Expression appendCondition(QString ph1, QString ph2, QVariant val1,
                                       QVariant val2, QString condition) const;
    QString entityClassname() const;
    QString separator;
    QSharedPointer<Schema> schema;
    QSharedPointer<Database> database;
};
}

#endif // QUERYBUILDER_H
