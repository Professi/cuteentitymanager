#ifndef CONDITION_H
#define CONDITION_H

#include <QStringList>
namespace CuteEntityManager {
class Condition {
  public:
    Condition();
    Condition(QString condition);
    void appendCondition(const QString &value);
    QStringList getConditions() const;
    void setConditions(const QStringList &value);

    void addSubCondition(const Condition &value);
    QList<Condition> getSubConditions() const;
    void setSubConditions(const QList<Condition> &value);

  private:
    QStringList conditions;
    QList<Condition> subConditions;
};
}

#endif // CONDITION_H
