#ifndef TABLESCHEMA_H
#define TABLESCHEMA_H
#include <QString>
#include <QList>
#include <QHash>
#include "columnschema.h"

namespace CuteEntityManager {

class TableSchema {
  public:
    TableSchema();
    ~TableSchema();
    virtual ColumnSchema const getColumn(QString name) const;
    virtual QList<QString> const getColumnNames();

    QString getSchemaName() const;
    void setSchemaName(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getFullName() const;
    void setFullName(const QString &value);

    QList<QString> getPrimaryKeys() const;
    void setPrimaryKeys(const QList<QString> &value);

    QString getSequenceName() const;
    void setSequenceName(const QString &value);

    QHash<QString, QString> getForeignKeys() const;
    void setForeignKeys(const QHash<QString, QString> &value);

    QList<ColumnSchema> getColumns() const;
    void setColumns(const QList<ColumnSchema> &value);

  private:
    QString schemaName;
    QString name;
    QString fullName;
    QList<QString> primaryKeys;
    QString sequenceName;
    QHash<QString, QString> foreignKeys;
    QList<ColumnSchema> columns;


};

}
#endif // TABLESCHEMA_H
