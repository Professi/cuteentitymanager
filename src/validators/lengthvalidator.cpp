#include "lengthvalidator.h"
using namespace CuteEntityManager;
LengthValidator::LengthValidator() : Validator() {

}


ErrorMsg LengthValidator::validateParam(QVariant value, Param param) const {
    QString val = value.toString();
    if (param.getName() == "min" && val.length() < param.getValue().toLongLong()) {
        return ErrorMsg(param.getName(),
                        "<property> must have more than " + param.getValue().toString() +
                        " characters.");
    } else if (param.getName() == "max"
               && val.length() > param.getValue().toLongLong() ) {
        return ErrorMsg(param.getName(),
                        "<property> must have more than " + param.getValue().toString() +
                        "characters.");
    }
    return ErrorMsg();
}
