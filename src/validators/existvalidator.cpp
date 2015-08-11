#include "existvalidator.h"
#include "../entity.h"
#include "../entityinstancefactory.h"
using namespace CuteEntityManager;
ExistValidator::ExistValidator() : Validator() {
}

ErrorMsg ExistValidator::validateParam(QVariant value, Param param) const {
    Q_UNUSED(param)
    QSharedPointer<Entity> entity = EntityInstanceFactory::castQVariant(value);
    if (!entity || entity->getId() <= -1) {
        return ErrorMsg("", "<property> is invalid.");
    }
    return ErrorMsg();
}

