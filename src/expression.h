#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QHash>
#include <QString>
#include <QVariant>
namespace CuteEntityManager {
class Expression {
  public:
    Expression();
    Expression(QString expression,
               bool onlyColumn = false);
    QString getExpression() const;
    void setExpression(const QString &value);

    QString toString() const;

    bool getOnlyColumn() const;
    void setOnlyColumn(bool value);

  private:
    QString expression;
    bool onlyColumn;
};
}
#endif // EXPRESSION_H
