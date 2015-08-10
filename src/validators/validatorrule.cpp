#include "validatorrule.h"
using namespace CuteEntityManager;

ValidationRule::ValidationRule() {
}

ValidationRule::ValidationRule(QString validatorName,
                               QString attributeName, QList<Param> params) {
    this->validatorName = validatorName;
    this->attributes = QStringList(attributeName);
    this->params = params;
}

ValidationRule::ValidationRule(QString validatorName,
                               QString attributeName, Param param) {
    this->validatorName = validatorName;
    this->attributes = QStringList(attributeName);
    if (!param.getName().isEmpty()) {
        this->params.append(param);
    }
}

ValidationRule::ValidationRule(QString validatorName,
                               QStringList attributeNames, QList<Param> params) {
    this->validatorName = validatorName;
    this->attributes = attributeNames;
    this->params = params;
}

ValidationRule::ValidationRule(QString validatorName,
                               QStringList attributeNames, Param param) {
    this->validatorName = validatorName;
    this->attributes = attributeNames;
    if (!param.getName().isEmpty()) {
        this->params.append(param);
    }
}

ValidationRule::ValidationRule(QString validatorName, QString attributeName,
                               QString paramName, QString paramValue) {
    this->validatorName = validatorName;
    this->attributes = QStringList(attributeName);
    this->params.append(Param(paramName, paramValue));
}

ValidationRule::ValidationRule(QString validatorName, QString attributeName,
                               QString paramName1, QVariant paramValue1, QString paramName2,
                               QVariant paramValue2) {
    this->validatorName = validatorName;
    this->attributes = QStringList(attributeName);
    params.append(Param(paramName1, paramValue1));
    params.append(Param(paramName2, paramValue2));
}

ValidationRule::ValidationRule(QString validatorName,
                               QStringList attributeNames,
                               QString paramName, QVariant paramValue) {
    this->validatorName = validatorName;
    this->attributes = attributeNames;
    this->params.append(Param(paramName, paramValue));
}

ValidationRule::ValidationRule(QString validatorName,
                               QStringList attributeNames,
                               QString paramName1, QVariant paramValue1, QString paramName2,
                               QVariant paramValue2) {
    this->validatorName = validatorName;
    this->attributes = attributeNames;
    params.append(Param(paramName1, paramValue1));
    params.append(Param(paramName2, paramValue2));
}

ValidationRule::~ValidationRule() {
}

QString ValidationRule::getValidatorName() const {
    return validatorName;
}

void ValidationRule::setValidatorName(const QString &value) {
    validatorName = value;
}
QStringList ValidationRule::getAttributes() const {
    return attributes;
}

void ValidationRule::setAttributes(const QStringList &value) {
    attributes = value;
}
QList<Param> ValidationRule::getParams() const {
    return params;
}

void ValidationRule::setParams(const QList<Param> &value) {
    params = value;
}
