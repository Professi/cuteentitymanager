#include "validatorfactory.h"
#include "defaultvalidator.h"
using namespace CuteEntityManager;

ValidatorFactory::ValidatorFactory() {
}

QHash<QByteArray, ValidatorFactory::Constructor> ValidatorFactory::instance =
    QHash<QByteArray, ValidatorFactory::Constructor>();

QHash<QString, QSharedPointer<Validator>> ValidatorFactory::validatorInstances =
        QHash<QString, QSharedPointer<Validator>>();


Validator *ValidatorFactory::createValidator(const QString &shortname) {
    if (Validator::builtInValidators().contains(shortname)) {
        return ValidatorFactory::createObject(Validator::builtInValidators().value(
                shortname).toLatin1());
    }
    return nullptr;
}

Validator *ValidatorFactory::createObject(const QByteArray &className) {
    Constructor constructor = ValidatorFactory::instance.value(className);
    if ( constructor == nullptr ) {
        return nullptr;
    }
    return (*constructor)();
}

QSharedPointer<Validator> ValidatorFactory::getValidatorObject(
    const QString &shortname) {
    if (!ValidatorFactory::validatorInstances.contains(shortname)) {
        ValidatorFactory::validatorInstances.insert(shortname,
                QSharedPointer<Validator>(ValidatorFactory::createValidator(shortname)));
    }
    return ValidatorFactory::validatorInstances.value(shortname);
}

void ValidatorFactory::registerClasses() {
    if (ValidatorFactory::instance.isEmpty()) {
        //        Validator::registerClass<CompareValidator>();
        ValidatorFactory::registerClass<DefaultValidator>();
        //        Validator::registerClass<EmailValidator>();
        //        Validator::registerClass<ExistValidator>();
//        Validator::registerClass<ImageValidator>();
//        Validator::registerClass<SizeValidator>();
//        Validator::registerClass<NumberValidator>();
//        Validator::registerClass<DateValidator>();
//        Validator::registerClass<RequiredValidator>();
//        Validator::registerClass<UniqueValidator>();
//        Validator::registerClass<UrlValidator>();
    }
}
