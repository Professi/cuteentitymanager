#ifndef JOIN_H
#define JOIN_H
#include <QString>
#include "condition.h"
namespace CuteEntityManager {
class Join {
  public:
    Join();
    explicit Join(QString foreignTable, QString condition,
         QString type = QStringLiteral("LEFT JOIN"));
    explicit Join(QString foreignTable, Condition condition,
         QString type = QStringLiteral("LEFT JOIN"));

    QString getType() const;
    void setType(const QString &value);

    QString getForeignTable() const;
    void setForeignTable(const QString &value);

    Condition getCondition() const;
    QString getMainCondition() const;
    void setCondition(const Condition &value);

private:
    QString type = QStringLiteral("LEFT JOIN");
    QString foreignTable;
    Condition condition;

};
}
#endif // JOIN_H
