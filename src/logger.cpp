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

void Logger::lastError(const QSqlQuery &q) {
    QFile log(this->getPath());
    log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    log.seek(log.size());
    QTextStream stream(&log);
    qDebug() << this->generateLogMsg(q.lastError());
    qDebug() << generateLogMsg(q);
    stream << this->generateLogMsg(q.lastError());
    stream << generateLogMsg(q);
    log.close();
}

void Logger::lastError(const QSqlError &e) {
    if(e.isValid()) {
        QFile log(this->getPath());
        log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
        log.seek(log.size());
        QTextStream stream(&log);
        qDebug() << this->generateLogMsg(e);
        stream << this->generateLogMsg(e);
        log.close();
    }
}

QString Logger::generateLogMsg(const QSqlQuery &q) const {
    QString r = "Query:<" + q.executedQuery() + ">";
    QMap<QString, QVariant> m = q.boundValues();
    QMap<QString,QVariant>::iterator i;
    for (i = m.begin(); i != m.end(); ++i) {
        r += "\n<" + i.key() + "|" + i.value().toString() + ">";
    }
    return r;
}

QString Logger::getPath() {
    if(this->path.isEmpty()) {
        this->path = this->defaultPath();
    }
    return path;
}

void Logger::setPath(const QString &value) {
    path = value;
}

QString Logger::generateLogMsg(const QSqlError &e) const {
    return "UTC:" + QDateTime::currentDateTime().toString("yyyy-MM-dd|hh:MM:ss") + "|" + e.driverText() + "|" + e.databaseText().toLatin1() + "\n";
}
