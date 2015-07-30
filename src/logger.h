#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>

class Logger
{
public:
    Logger(QString path="");
    ~Logger();
    QString defaultPath() const;

    void lastError(const QSqlError &e);
    void lastError(const QSqlQuery &q, bool logQuery=false);
    QString getPath();
    void setPath(const QString &value);

protected:
    QString generateLogMsg(const QSqlError &e) const;
    QString generateLogMsg(const QSqlQuery &q) const;

private:
    QString path;
};

#endif // LOGGER_H
