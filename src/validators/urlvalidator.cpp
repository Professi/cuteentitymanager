#include "urlvalidator.h"
using namespace CuteEntityManager;
#include <QRegularExpression>
UrlValidator::UrlValidator() : Validator() {

}

ErrorMsg UrlValidator::validateParam(QVariant value, Param param) const {
    QString val = value.toString();
    if (val.size() < 2000) {
        if (param.getName() == "defaultScheme" && !param.getValue().isNull()) {
            val = param.getValue().toString() + "://" + val;
        }
        QString pattern = "";
        if (this->pattern.indexOf("{schemes}") != -1) {
            QString replacement = "(";
            bool first = true;
            for (int i = 0; i < this->validSchemes.size(); ++i) {
                if (first) {
                    first = false;
                } else {
                    replacement += "|";
                }
                replacement += this->validSchemes.at(i);
            }
            replacement += ")";
            pattern = this->getPattern().replace("{schemes}", replacement);
        } else {
            pattern = this->pattern;
        }
        QRegularExpression regExp = QRegularExpression(pattern);
        if (regExp.match(val).hasMatch()) {
            return ErrorMsg();
        } else {
            return ErrorMsg(param.getName(), "Value is not a valid URL.");
        }
    }
    return ErrorMsg();
}

QStringList UrlValidator::getValidSchemes() const {
    return validSchemes;
}

void UrlValidator::setValidSchemes(const QStringList &value) {
    validSchemes = value;
}
QString UrlValidator::getPattern() const {
    return pattern;
}

void UrlValidator::setPattern(const QString &value) {
    pattern = value;
}


