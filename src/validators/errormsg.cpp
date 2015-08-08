#include "errormsg.h"
using namespace CuteEntityManager;
ErrorMsg::ErrorMsg() {
}

ErrorMsg::~ErrorMsg() {
}

ErrorMsg::ErrorMsg(QString param, QString errorMsg, QString propertyName) {
    this->param = param;
    this->errorMsg = errorMsg;
    this->propertyName = propertyName;
}

QString ErrorMsg::getParam() const {
    return param;
}

void ErrorMsg::setParam(const QString &value) {
    param = value;
}

QString ErrorMsg::getPropertyName() const {
    return propertyName;
}

void ErrorMsg::setPropertyName(const QString &value) {
    propertyName = value;
}

QString ErrorMsg::getErrorMsg() const {
    return errorMsg;
}

void ErrorMsg::setErrorMsg(const QString &value) {
    errorMsg = value;
}
