#include "patternvalidator.h"
#include <QRegularExpression>
using namespace CuteEntityManager;
PatternValidator::PatternValidator() : Validator() {
}

ErrorMsg PatternValidator::validateParam(QVariant value, Param param) const {
    QRegularExpression regExp = QRegularExpression();
    if (param.getName().isEmpty()) {
        regExp.setPattern(param.getValue().toString());
    } else {
        regExp.setPattern(param.getName());
    }
    if (regExp.match(value.toString()).hasMatch()) {
        return ErrorMsg();
    }
    return ErrorMsg(param.getName(), "<property> not matches the pattern.");
}

