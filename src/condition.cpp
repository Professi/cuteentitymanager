#include "condition.h"
using namespace CuteEntityManager;
Condition::Condition() {

}

Condition::Condition(QString condition) {
    if (!condition.isEmpty()) {
        this->conditions.append(condition);
    }
}

void Condition::appendCondition(const QString &value) {
    this->conditions.append(value);
}

QStringList Condition::getConditions() const {
    return conditions;
}

void Condition::setConditions(const QStringList &value) {
    conditions = value;
}

QList<Condition> Condition::getSubConditions() const {
    return subConditions;
}

void Condition::setSubConditions(const QList<Condition> &value) {
    subConditions = value;
}

void CuteEntityManager::Condition::addSubCondition(const
        CuteEntityManager::Condition &value) {
    this->subConditions.append(value);
}
