#ifndef JOIN_H
#define JOIN_H
#include <QString>

namespace CuteEntityManager {
class Join {

  public:
    Join();
    Join(QString foreignTable, QString condition,
         QString type = QStringLiteral("LEFT JOIN"));

    QString getType() const;
    void setType(const QString &value);

    QString getForeignTable() const;
    void setForeignTable(const QString &value);

    QString getCondition() const;
    void setCondition(const QString &value);

  private:
    QString type = QStringLiteral("LEFT JOIN");
    QString foreignTable;
    QString condition;

};
}
#endif // JOIN_H
