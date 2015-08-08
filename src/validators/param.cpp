#include "param.h"
using namespace CuteEntityManager;

Param::Param() {
}

Param::~Param() {
}

Param::Param(QString name, QVariant value) {
    this->value = value;
    this->name = name;
}

QVariant Param::getValue() const {
    return value;
}

void Param::setValue(QVariant value) {
    value = value;
}

QString Param::getName() const {
    return name;
}

void Param::setName(const QString &value) {
    name = value;
}


