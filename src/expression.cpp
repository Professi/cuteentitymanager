#include "expression.h"
using namespace CuteEntityManager;
Expression::Expression() {
}

Expression::Expression(QString expression,
                       bool onlyColumn) {
    this->expression = expression;
    this->onlyColumn = onlyColumn;
}

QString Expression::getExpression() const {
    return this->expression;
}

void Expression::setExpression(const QString &value) {
    this->expression = value;
}

QString Expression::toString() const {
    return this->expression;
}

bool Expression::getOnlyColumn() const {
    return onlyColumn;
}

void Expression::setOnlyColumn(bool value) {
    onlyColumn = value;
}

