#include "join.h"
using namespace CuteEntityManager;
Join::Join() {

}

Join::Join(QString foreignTable, QString condition, QString type) {
    this->foreignTable = foreignTable;
    this->condition = Condition(condition);
    this->type = type;
}

Join::Join(QString foreignTable, Condition condition, QString type) {
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

Condition Join::getCondition() const {
    return condition;
}

QString Join::getMainCondition() const {
    auto conditions = this->condition.getConditions();
    if (!conditions.isEmpty()) {
        return conditions.at(0);
    } else {
        return "";
    }
}

void Join::setCondition(const Condition &value) {
    condition = value;
}

