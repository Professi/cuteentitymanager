#include "validator.h"
#include "validatorfactory.h"
#include <QDebug>
using namespace CuteEntityManager;
Validator::Validator() : QObject() {
    ValidatorFactory::registerClasses();
}

Validator::~Validator() {
}

const QHash<QString, QString> Validator::builtInValidators() {
    QHash<QString, QString> hash = QHash<QString, QString>();
    hash.insert("compare", "CuteEntityManager::CompareValidator");
    hash.insert("default", "CuteEntityManager::DefaultValidator");
    hash.insert("email", "CuteEntityManager::EmailValidator");
    hash.insert("exists", "CuteEntityManager::ExistValidator");
    hash.insert("file", "CuteEntityManager::FileValidator");
    hash.insert("image", "CuteEntityManager::ImageValidator");
    hash.insert("number", "CuteEntityManager::NumberValidator");
    hash.insert("date", "CuteEntityManager::DateValidator");
    hash.insert("required", "CuteEntityManager::RequiredValidator");
    hash.insert("unique", "CuteEntityManager::UniqueValidator");
    hash.insert("url", "CuteEntityManager::UrlValidator");
    hash.insert("pattern", "CuteEntityManager::PatternValidator");
    hash.insert("length", "CuteEntityManager::LengthValidator");
    return hash;
}

QList<ErrorMsg> Validator::validate(QVariant value, QList<Param> params) const {
    QList<ErrorMsg> msgs = QList<ErrorMsg>();
    if (params.isEmpty()) {
        params.append(Param(""));
    }
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
