#include "defaultvalidator.h"
#include "validator.h"
using namespace CuteEntityManager;
DefaultValidator::DefaultValidator() : Validator() {
}

ErrorMsg DefaultValidator::validateParam(QVariant value, Param param) const {
    if (value != param.getValue()) {
        return ErrorMsg(param.getName(), "Default value not set");
    }
    return ErrorMsg();
}

