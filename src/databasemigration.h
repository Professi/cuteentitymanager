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
    DatabaseMigration();
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
