#include "requiredvalidator.h"
using namespace CuteEntityManager;
RequiredValidator::RequiredValidator(): Validator() {
}

ErrorMsg RequiredValidator::validateParam(QVariant value, Param param) const {
    if (value.isNull()) {
        return ErrorMsg(param.getName(), "Value is not set");
    }
    return ErrorMsg();
}
