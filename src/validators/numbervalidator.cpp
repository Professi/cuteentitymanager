#include "numbervalidator.h"
using namespace CuteEntityManager;
NumberValidator::NumberValidator() : Validator() {

}

ErrorMsg NumberValidator::validateParam(QVariant value, Param param) const {
    bool convert;
    double converted = value.toDouble(&convert);
    if (!convert) {
        return ErrorMsg(param.getName(), "Value could not converted.");
    }
    if (param.getName() == "min" && param.getValue().toDouble() > converted) {
        return ErrorMsg(param.getName(),
                        "<property> must be no less than " + QString::number(param.getValue().toDouble()) +
                        ".");
    } else if (param.getName() == "max"
               && param.getValue().toDouble() < converted) {
        return ErrorMsg(param.getName(),
                        "<property> must be not greater than " + QString::number(param.getValue().toDouble())
                        + ".");
    }
    return ErrorMsg();
}
