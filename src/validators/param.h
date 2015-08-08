#ifndef PARAM_H
#define PARAM_H

#include <QString>
#include <QVariant>
namespace CuteEntityManager {
class Param {
  public:
    Param();
    ~Param();
    Param(QString name, QVariant value = QVariant());
    QVariant getValue() const;
    void setValue(QVariant value);

    QString getName() const;
    void setName(const QString &value);

  private:
    QVariant value;
    QString name;
};
}

#endif // PARAM_H
