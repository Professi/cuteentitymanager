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
