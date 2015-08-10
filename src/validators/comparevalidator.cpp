#include "comparevalidator.h"
using namespace CuteEntityManager;
CompareValidator::CompareValidator() : Validator() {
}

ErrorMsg CompareValidator::validateParam(QVariant value, Param param) const {
    if (param.getName() == "==" && value != param.getValue()) {
        return ErrorMsg(param.getName(), "<property> must be repeated exactly.");
    } else if (param.getName() == "!="  && value == param.getValue()) {
        return ErrorMsg(param.getName(),
                        "<property> must not be equal to " + param.getValue().toString() + ".");
    } else if (param.getName() == ">"  && value <= param.getValue()) {
        return ErrorMsg(param.getName(),
                        "<property> must be greater than " + param.getValue().toString() + ".");
    } else if (param.getName() == "<"  && value >= param.getValue()) {
        return ErrorMsg(param.getName(),
                        "<property> must be greater than or equal to " + param.getValue().toString() +
                        ".");
    } else if (param.getName() == ">=" && value < param.getValue()) {
        return ErrorMsg(param.getName(),
                        "<property> must be less than " + param.getValue().toString() + ".");
    } else if (param.getName() == "<="  && value > param.getValue()) {
        return ErrorMsg(param.getName(),
                        "<property> must be less than or equal to " + param.getValue().toString() +
                        ".");
    }
    return ErrorMsg();
}

QString CompareValidator::getDefaultOperator() const {
    return defaultOperator;
}

void CompareValidator::setDefaultOperator(const QString &value) {
    defaultOperator = value;
}


