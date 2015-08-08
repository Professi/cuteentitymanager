#include "validatorfactory.h"
#include "defaultvalidator.h"
using namespace CuteEntityManager;
ValidatorFactory::ValidatorFactory() {
}


QHash<QByteArray, ValidatorFactory::Constructor> ValidatorFactory::instance =
    QHash<QByteArray, ValidatorFactory::Constructor>();


Validator *ValidatorFactory::createValidator(QString shortname) {
    if (Validator::builtInValidators().contains(shortname)) {
        return ValidatorFactory::createObject(shortname.toLatin1());
    }
    return nullptr;
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
