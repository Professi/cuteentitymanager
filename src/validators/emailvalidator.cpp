#include "emailvalidator.h"
#include <QRegularExpression>
using namespace CuteEntityManager;
EmailValidator::EmailValidator() : Validator() {

}

ErrorMsg EmailValidator::validateParam(QVariant value, Param param) const {
    QRegularExpression exp = QRegularExpression();
    QString val = value.toString();
    if (!val.isEmpty()) {
        if (param.getName() == "full") {
            exp.setPattern(this->getFullPattern());
        } else {
            exp.setPattern(this->getPattern());
        }
        if (exp.match(val).hasMatch()) {
            return ErrorMsg();
        }
        return ErrorMsg(param.getName(), "<property> is not a valid email address.");
    }
    return ErrorMsg();
}

QString EmailValidator::getPattern() const {
    return pattern;
}

void EmailValidator::setPattern(const QString &value) {
    pattern = value;
}
QString EmailValidator::getFullPattern() const {
    return fullPattern;
}

void EmailValidator::setFullPattern(const QString &value) {
    fullPattern = value;
}



