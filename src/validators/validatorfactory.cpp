#include "validatorfactory.h"
#include "defaultvalidator.h"
#include "requiredvalidator.h"
#include "numbervalidator.h"
#include "comparevalidator.h"
#include "emailvalidator.h"
#include "existvalidator.h"
#include "filevalidator.h"
#include "imagevalidator.h"
#include "datevalidator.h"
#include "requiredvalidator.h"
#include "urlvalidator.h"
#include "uniquevalidator.h"
#include "patternvalidator.h"
#include "lengthvalidator.h"
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
        ValidatorFactory::registerClasses();
        ValidatorFactory::validatorInstances.insert(shortname,
                QSharedPointer<Validator>(ValidatorFactory::createValidator(shortname)));
    }
    return ValidatorFactory::validatorInstances.value(shortname);
}

void ValidatorFactory::registerClasses() {
    if (ValidatorFactory::instance.isEmpty()) {
        ValidatorFactory::registerClass<CompareValidator>();
        ValidatorFactory::registerClass<DefaultValidator>();
        ValidatorFactory::registerClass<EmailValidator>();
        ValidatorFactory::registerClass<ExistValidator>();
        ValidatorFactory::registerClass<FileValidator>();
        ValidatorFactory::registerClass<ImageValidator>();
        ValidatorFactory::registerClass<NumberValidator>();
        ValidatorFactory::registerClass<DateValidator>();
        ValidatorFactory::registerClass<RequiredValidator>();
        ValidatorFactory::registerClass<PatternValidator>();
        ValidatorFactory::registerClass<UniqueValidator>();
        ValidatorFactory::registerClass<UrlValidator>();
        ValidatorFactory::registerClass<LengthValidator>();
    }
}
