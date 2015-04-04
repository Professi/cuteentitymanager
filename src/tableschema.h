#ifndef TABLESCHEMA_H
#define TABLESCHEMA_H
#include <QString>
#include <QList>
#include <QStringList>
#include <QHash>
#include <QSharedPointer>
#include <QSqlField>
#include <QSqlRelation>
namespace CuteEntityManager {

class TableSchema {
  public:
    TableSchema();
    ~TableSchema();
    virtual QSharedPointer<QSqlField> const getColumn(QString name) const;
    virtual const QStringList getColumnNames();

    QString getSchemaName() const;
    void setSchemaName(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getFullName() const;
    void setFullName(const QString &value);

    QStringList getPrimaryKeys() const;
    void setPrimaryKeys(const QStringList &value);

    QString getSequenceName() const;
    void setSequenceName(const QString &value);

    QHash<QString, QSharedPointer<QSqlField> > getColumns() const;
    void setColumns(const QHash<QString, QSharedPointer<QSqlField> > &value);

    QHash<QString, QSharedPointer<QSqlRelation> > getRelations() const;
    void setRelations(const QHash<QString, QSharedPointer<QSqlRelation> > &value);

private:
    QString schemaName;
    QString name;
    QString fullName;
    QStringList primaryKeys;
    QString sequenceName;
    QHash<QString, QSharedPointer<QSqlRelation>>  relations;
    QHash<QString, QSharedPointer<QSqlField>> columns;
};

}
#endif // TABLESCHEMA_H
