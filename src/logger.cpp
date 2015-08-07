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
        QFile log(this->getPath());
        log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        log.seek(log.size());
        QTextStream stream(&log);
        const QString errorMsg = this->generateLogMsg(q.lastError());
        if (!errorMsg.isEmpty()) {
            qWarning() << errorMsg;
            stream << errorMsg;
        }
        if (logQuery || !errorMsg.isEmpty()) {
            const QString query = this->generateLogMsg(q);
            if (!query.isEmpty()) {
                qDebug() << query;
                stream << query;
            }
        }
        stream << "\n";
        stream.flush();
        log.close();
    }
}

void Logger::lastError(const QSqlError &e) {
    if (e.isValid()) {
        QFile log(this->getPath());
        log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        log.seek(log.size());
        QTextStream stream(&log);
        qDebug() << this->generateLogMsg(e);
        stream << this->generateLogMsg(e);
        stream << "\n";
        stream.flush();
        log.close();
    }
}

QString Logger::generateLogMsg(const QSqlQuery &q, bool withValues) const {
    QString r = "<" + q.executedQuery() + ">";
    if (withValues) {
        QMap<QString, QVariant> m = q.boundValues();
        QMap<QString, QVariant>::iterator i;
        if (!m.isEmpty()) {
            r += "Values: ";
            for (i = m.begin(); i != m.end(); ++i) {
                r += "{" + i.key() + "=" + i.value().toString() + "}";
            }
        }
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
        r = "ErrorUTC:" +
            QDateTime::currentDateTime().toString("yyyy-MM-dd|hh:MM:ss") + "|" +
            e.driverText() + "|" + e.databaseText().toLatin1();
    }
    return r;
}
