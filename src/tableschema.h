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
#ifndef TABLESCHEMA_H
#define TABLESCHEMA_H
#include <QString>
#include <QList>
#include <QStringList>
#include <QHash>
#include <QSharedPointer>
#include <QSqlField>
#include <QSqlRelation>
#include <QSqlRelationalTableModel>
namespace CuteEntityManager {

class TableSchema {
  public:
    TableSchema();
    virtual ~TableSchema();
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

    QSharedPointer<QSqlRelationalTableModel> getTableModel() const;

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
