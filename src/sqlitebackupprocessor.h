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
#ifndef SQLITEBACKUPPROCESSOR_H
#define SQLITEBACKUPPROCESSOR_H

#include <QObject>
#include <QtSql/QSqlDriver>
#include <QString>
#include <QVariant>
#include "database.h"
namespace CuteEntityManager {
class SqliteBackupProcessor : public QObject {
  public:
    explicit SqliteBackupProcessor(QSharedPointer<Database> database, QString destination);
    ~SqliteBackupProcessor();
    QSharedPointer<Database> getDatabase() const;
    void setDatabase(const QSharedPointer<Database> &value);

    QString getDestination() const;
    void setDestination(const QString &value);

public slots:
    bool sqliteDBMemFile(bool save,QString fileName= "db.sqlite.bak");
private:
    QSharedPointer<Database> database;
    QString destination;
};
}

#endif // SQLITEBACKUPPROCESSOR_H
