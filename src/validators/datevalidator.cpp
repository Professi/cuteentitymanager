#include "datevalidator.h"
#include <QDate>
#include <QLocale>
using namespace CuteEntityManager;
DateValidator::DateValidator() : Validator() {

}

ErrorMsg DateValidator::validateParam(QVariant value, Param param) const {
    QDate date = value.toDate();
    if (date.isValid()) {
        if (param.getName() == "future") {
            if (date < QDate::currentDate()) {
                ErrorMsg(param.getName(), "Date is not in the future.");
            }
        } else if (param.getName() == "past") {
            if (date > QDate::currentDate()) {
                ErrorMsg(param.getName(), "Date is not in the past.");
            }

        } else if (param.getName() == "min" && date < param.getValue().toDate()) {
            ErrorMsg(param.getName(),
                     "Date must be no less than " + param.getValue().toString());
        } else if (param.getName() == "max" && date > param.getValue().toDate()) {
            ErrorMsg(param.getName(),
                     "Date must be no greater than " + param.getValue().toString());
        }
    }
    //cause we don't want to replace functionality of RequiredValidator
    return ErrorMsg();
}

