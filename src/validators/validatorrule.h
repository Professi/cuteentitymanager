#ifndef VALIDATORATTRIBUTE_H
#define VALIDATORATTRIBUTE_H
#include <QString>
#include <QStringList>
#include "param.h"
namespace CuteEntityManager {
class ValidationRule {
  public:
    ValidationRule();
    explicit ValidationRule(QString validatorName, QString attributeName,
                            QList<Param> params = QList<Param>());
    explicit ValidationRule(QString validatorName, QString attributeName,
                            Param param);
    explicit ValidationRule(QString validatorName, QStringList attributeNames,
                            QList<Param> params = QList<Param>());
    explicit ValidationRule(QString validatorName, QStringList attributeNames,
                            Param param);
    explicit ValidationRule(QString validatorName, QString attributeName,
                            QString paramName, QString paramValue);
    explicit ValidationRule(QString validatorName, QString attributeName,
                            QString paramName1, QVariant paramValue1, QString paramName2,
                            QVariant paramValue2);
    explicit ValidationRule(QString validatorName, QStringList attributeNames,
                            QString paramName, QVariant paramValue = QVariant());
    explicit ValidationRule(QString validatorName, QStringList attributeNames,
                            QString paramName1, QVariant paramValue1, QString paramName2,
                            QVariant paramValue2);

    ~ValidationRule();
    QString getValidatorName() const;
    void setValidatorName(const QString &value);

    QStringList getAttributes() const;
    void setAttributes(const QStringList &value);

    QList<Param> getParams() const;
    void setParams(const QList<Param> &value);

  private:
    QString validatorName;
    QStringList attributes;
    QList<Param> params;
};
}


#endif // VALIDATORATTRIBUTE_H
