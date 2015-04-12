#include "relation.h"
using namespace CuteEntityManager;

Relation::Relation() {
}

Relation::Relation(QString propertyName, RelationType type, bool optional) {
    this->propertyName = propertyName;
    this->type = type;
    this->optional = optional;
}

Relation::~Relation() {
}

RelationType Relation::getType() const {
    return type;
}

void Relation::setType(const RelationType &value) {
    type = value;
}

QString Relation::getPropertyName() const {
    return propertyName;
}

void Relation::setPropertyName(const QString &value) {
    propertyName = value;
}
bool Relation::getOptional() const {
    return optional;
}

void Relation::setOptional(bool value) {
    optional = value;
}
