#ifndef ORDERBY_H
#define ORDERBY_H

#include <QString>
#include "expression.h"
namespace CuteEntityManager {
enum class Direction {
    SORT_ASC,
    SORT_DESC,
    DEFAULT
};

//class Expression;
class OrderBy {
  public:
    OrderBy();
    OrderBy(QString column, Direction direction = Direction::DEFAULT);
    OrderBy(Expression direction);
    QString getColumn() const;
    void setColumn(const QString &value);

    Direction getDirection() const;
    void setDirection(const Direction &value);

    Expression getExpressedDirection() const;
    void setExpressedDirection(const Expression &value);

  private:
    QString column;
    Direction direction;
    Expression expressedDirection;
};
}
#endif // ORDERBY_H
