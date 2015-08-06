#include "orderby.h"
using namespace CuteEntityManager;
OrderBy::OrderBy() {
    this->direction = Direction::DEFAULT;
}

OrderBy::OrderBy(QString column, Direction direction) {
    this->column = column;
    this->direction = direction;
}

OrderBy::OrderBy(Expression direction) {
    this->column = "";
    this->expressedDirection = direction;
}

QString OrderBy::getColumn() const {
    return column;
}

void OrderBy::setColumn(const QString &value) {
    column = value;
}

Direction OrderBy::getDirection() const {
    return direction;
}

void OrderBy::setDirection(const Direction &value) {
    direction = value;
}

Expression OrderBy::getExpressedDirection() const {
    return expressedDirection;
}

void OrderBy::setExpressedDirection(const Expression &value) {
    expressedDirection = value;
}

