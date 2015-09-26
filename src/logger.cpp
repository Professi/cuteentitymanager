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
#include "logger.h"
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QDateTime>

using namespace CuteEntityManager;
Logger::Logger(QString path) {
    this->path = path;
}

Logger::~Logger() {
}

QString Logger::defaultPath() const {
    return QDir::currentPath() + "/errors.log";
}

void Logger::lastError(const QSqlQuery &q, bool logQuery) {
    if (logQuery || q.lastError().isValid()) {
        const QString errorMsg = this->generateLogMsg(q.lastError());
        if (logQuery || !errorMsg.isEmpty()) {
            QString msg = "{" + QString("\"time\":\"") +
                          QDateTime::currentDateTime().toString(Qt::ISODate) + QString("\"") + errorMsg;
            msg += this->generateLogMsg(q) + "}";
            this->logMsg(msg);
            if (errorMsg.isEmpty()) {
                qDebug() << msg.replace("\"", "'");
            } else {
                qWarning() << msg.replace("\"", "'");
            }
        }
    }
}

void Logger::lastError(const QSqlError &e) {
    if (e.isValid()) {
        this->logMsg(this->generateLogMsg(e));
    }
}

void Logger::logMsg(const QString &value) {
    QFile log(this->getPath());
    log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    log.seek(log.size());
    QTextStream stream(&log);
    stream.setCodec("UTF-8");
    stream << value;
    stream << "\n";
    stream.flush();
    log.close();
}

QString Logger::generateLogMsg(const QSqlQuery &q, bool withValues) const {
    QString r = ", \"query\":\"" + q.executedQuery() + "\"";
    if (withValues) {
        QMap<QString, QVariant> m = q.boundValues();
        if (!m.isEmpty()) {
            r += ", \"values\": {";
            bool first = true;
            for (auto i = m.begin(); i != m.end(); ++i) {
                if (first) {
                    first = false;
                }  else {
                    r += ", ";
                }
                r += "\"" + i.key().mid(1) + "\":\"" + i.value().toString() + "\"";
            }
        }
        r += "}";
    }
    return r;
}

QString Logger::getPath() {
    if (this->path.isEmpty()) {
        this->path = this->defaultPath();
    }
    return path;
}

void Logger::setPath(const QString &value) {
    path = value;
}

QString Logger::generateLogMsg(const QSqlError &e) const {
    QString r = "";
    if (e.isValid()) {
        r = ",\"error\":\"" + e.text() + "\",\"code\":\"" + e.number() + "\"";
    }
    return r;
}
