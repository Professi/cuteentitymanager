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
#include <QTimer>
#include <QDir>
#include "database.h"
namespace CuteEntityManager {
class SqliteBackupProcessor : public QObject {
  public:
    explicit SqliteBackupProcessor(QSharedPointer<Database> database,
                                   QString destination);
    /**
     * @brief SqliteBackupProcessor
     * @param database
     * @param destination
     * @param backupFilename
     * @param timer
     * @param incrementalBackups
     * @param backupCount
     * You must start the timer.
     */
    explicit SqliteBackupProcessor(QSharedPointer<Database> database,
                                   QString destination, QString backupFilename, QSharedPointer<QTimer> timer,
                                   bool incrementalBackups = false, int backupCount = 1);
    ~SqliteBackupProcessor();
    QSharedPointer<Database> getDatabase() const;
    void setDatabase(const QSharedPointer<Database> &value);

    QString getDestination() const;
    void setDestination(const QString &value);

    QString getBackupFilename() const;
    void setBackupFilename(const QString &value);

    int getBackupCount() const;
    void setBackupCount(int value);

    bool getIncrementalBackups() const;
    void setIncrementalBackups(bool value);

    QSharedPointer<QTimer> getTimer() const;
    void setTimer(const QSharedPointer<QTimer> &value);

  public slots:
    bool sqliteDBMemFile(bool save, QString fileName = "db.sqlite.bak");
    void backup();
  protected slots:
    void rotateBackup();

  private:
    QSharedPointer<Database> database;
    QString destination;
    QString backupFilename;
    QSharedPointer<QTimer> timer;
    bool incrementalBackups;
    int backupCount;
    int counter = 0;
};
}

#endif // SQLITEBACKUPPROCESSOR_H
