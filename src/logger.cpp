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
#include <QtGlobal>

using namespace CuteEntityManager;

Logger::Logger(QString path, MsgType min) {
    this->path = path;
    this->minimum = min;
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
            this->logMsg(msg, errorMsg.isEmpty() ? MsgType::DEBUG : MsgType::WARNING);
        }
    }
}

void Logger::lastError(const QSqlError &e) {
    if (e.isValid()) {
        this->logMsg(this->generateLogMsg(e), MsgType::WARNING);
    }
}

void Logger::logMsg(const QString &value, const MsgType type) {
    if (!value.isEmpty() && this->shouldBeLogged(type)) {
        QString msg = value;
        QFile log(this->getPath());
        log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        log.seek(log.size());
        QTextStream stream(&log);
        stream.setCodec("UTF-8");
        if (value.size() - 1 != value.lastIndexOf("\n")) {
            msg.append("\n");
        }
        stream << msg;
        this->outputToConsole(type, msg.replace("\"", "'"));
        stream.flush();
        log.close();
    }
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

bool Logger::shouldBeLogged(const MsgType &type) const {
    switch (type) {
    case MsgType::DEBUG:
        return this->minimum == MsgType::DEBUG;
    case MsgType::INFO:
        return this->minimum == MsgType::DEBUG || this->minimum == MsgType::INFO;
    case MsgType::WARNING:
        return this->minimum == MsgType::DEBUG || this->minimum == MsgType::INFO
               || this->minimum == MsgType::WARNING;
    case MsgType::CRITICAL:
        return this->minimum == MsgType::DEBUG || this->minimum == MsgType::INFO
               || this->minimum == MsgType::WARNING || this->minimum == MsgType::CRITICAL;
    default:
        return true;
        break;
    }
}

void Logger::outputToConsole(const MsgType &type, const QString &msg) const {
    switch (type) {
    case MsgType::DEBUG:
        qDebug() << msg;
        break;
#if QT_VERSION >= 0x050500
    case MsgType::INFO:
        qInfo() << msg;
        break;
    case MsgType::WARNING:
        qWarning() << msg;
        break;
#else
    case MsgType::INFO:
        qDebug() << msg;
        break;
    case MsgType::WARNING:
        qDebug() << msg;
        break;
#endif
    case MsgType::CRITICAL:
        qCritical() << msg;
        break;
    case MsgType::FATAL:
        qFatal(msg.toUtf8().constData());
        break;
    }
}

MsgType Logger::getMinimum() const {
    return minimum;
}

void Logger::setMinimum(const MsgType &value) {
    minimum = value;
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
