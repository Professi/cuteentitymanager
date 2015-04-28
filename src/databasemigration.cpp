#include "databasemigration.h"
using namespace CuteEntityManager;

DatabaseMigration::DatabaseMigration() : Entity() {

}

DatabaseMigration::DatabaseMigration(QString version, QDateTime applyTime) {
    this->version = version;
    this->applyTime = applyTime;
}

DatabaseMigration::~DatabaseMigration() {

}

QString DatabaseMigration::getVersion() const {
    return version;
}

void DatabaseMigration::setVersion(const QString &value) {
    version = value;
}

QDateTime DatabaseMigration::getApplyTime() const {
    return applyTime;
}

void DatabaseMigration::setApplyTime(const QDateTime &value) {
    applyTime = value;
}



