#include "join.h"
using namespace CuteEntityManager;
Join::Join() {

}

Join::Join(QString foreignTable, QString condition, QString type) {
    this->foreignTable = foreignTable;
    this->condition = condition;
    this->type = type;
}

QString Join::getType() const {
    return type;
}

void Join::setType(const QString &value) {
    type = value;
}

QString Join::getForeignTable() const {
    return foreignTable;
}

void Join::setForeignTable(const QString &value) {
    foreignTable = value;
}

QString Join::getCondition() const {
    return condition;
}

void Join::setCondition(const QString &value) {
    condition = value;
}


