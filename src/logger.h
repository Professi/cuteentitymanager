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
#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
namespace CuteEntityManager {

enum class MsgType { DEBUG, INFO, WARNING, CRITICAL, FATAL};

class Logger {
#ifdef QT_DEBUG
#define DEFAULTMSGTYPE MsgType::DEBUG
#else
#define DEFAULTMSGTYPE MsgType::CRITICAL
#endif

  public:
    Logger(QString path = "", MsgType min = DEFAULTMSGTYPE);
    ~Logger();
    QString defaultPath() const;

    void lastError(const QSqlError &e);
    void lastError(const QSqlQuery &q, bool logQuery = false);
    QString getPath();
    void setPath(const QString &value);
    void logMsg(const QString &value, const MsgType type = MsgType::DEBUG);

    MsgType getMinimum() const;
    void setMinimum(const MsgType &value);

  protected:
    QString generateLogMsg(const QSqlError &e) const;
    QString generateLogMsg(const QSqlQuery &q, bool withValues = true) const;
    bool shouldBeLogged(const MsgType &type) const;
    void outputToConsole(const MsgType &type, const QString &msg) const;


  private:
    QString path;
    MsgType minimum;
};
}
#endif // LOGGER_H
