#include "validator.h"
#include "validatorfactory.h"
using namespace CuteEntityManager;
Validator::Validator() : QObject() {
    ValidatorFactory::registerClasses();
}

Validator::~Validator() {
}

const QHash<QString, QString> Validator::builtInValidators() {
    QHash<QString, QString> hash = QHash<QString, QString>();
//    hash.insert("compare", "CompareValidator");
    hash.insert("default", "DefaultValidator");
//    hash.insert("email", "EmailValidator");
//    hash.insert("exist", "ExistValidator");
//    hash.insert("image", "ImageValidator");
//    hash.insert("size", "SizeValidator");
//    hash.insert("number", "NumberValidator");
//    hash.insert("date", "DateValidator");
    hash.insert("required", "RequiredValidator");
//    hash.insert("unique", "UniqueValidator");
//    hash.insert("url", "UrlValidator");
    return hash;
}

QList<ErrorMsg> Validator::validate(QVariant value, QList<Param> params) const {
    QList<ErrorMsg> msgs = QList<ErrorMsg>();
    for (int i = 0; i < params.size(); ++i) {
        ErrorMsg msg = this->validateParam(value, params.at(i));
        if (!msg.getErrorMsg().isEmpty()) {
            msgs.append(msg);
        }
    }
    return msgs;
}

QString Validator::generateErrorMsg(ErrorMsg msg) {
    if (msg.getPropertyName().isEmpty()) {
        //return tr(msg.getErrorMsg());
        return msg.getErrorMsg();
    }
    //return tr(msg.getErrorMsg()).replace("<property>", msg.getPropertyName());
    return msg.getErrorMsg().replace("<property>", msg.getPropertyName());
}
