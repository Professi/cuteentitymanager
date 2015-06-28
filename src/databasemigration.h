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
#ifndef DATABASEMIGRATION_H
#define DATABASEMIGRATION_H
#include "entity.h"
#include <QString>
#include <QDateTime>
namespace CuteEntityManager {
class DatabaseMigration : public Entity {

    Q_PROPERTY(QString version READ getVersion WRITE setVersion)
    Q_PROPERTY(QDateTime applyTime READ getApplyTime WRITE setApplyTime)

  public:
    Q_INVOKABLE DatabaseMigration();
    DatabaseMigration(QString version, QDateTime applyTime);
    ~DatabaseMigration();
    QString getVersion() const;
    void setVersion(const QString &value);

    QDateTime getApplyTime() const;
    void setApplyTime(const QDateTime &value);

  private:
    QString version;
    QDateTime applyTime;
};
}

#endif // DATABASEMIGRATION_H
