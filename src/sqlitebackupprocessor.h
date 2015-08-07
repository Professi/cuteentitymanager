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
    SqliteBackupProcessor(QSharedPointer<Database> database, QString destination);
    QSharedPointer<Database> getDatabase() const;
    void setDatabase(const QSharedPointer<Database> &value);

    QString getDestination() const;
    void setDestination(const QString &value);

public slots:
    bool backup(QString fileName);
private:
    QSharedPointer<Database> database;
    QString destination;
};
}

#endif // SQLITEBACKUPPROCESSOR_H
