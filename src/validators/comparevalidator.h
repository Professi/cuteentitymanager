#ifndef COMPAREVALIDATOR_H
#define COMPAREVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class CompareValidator : public Validator {
    Q_OBJECT
  public:
    CompareValidator();
    QString getDefaultOperator() const;
    void setDefaultOperator(const QString &value);

  protected:
    ErrorMsg validateParam(QVariant value, Param param) const final override;
    QString defaultOperator = QStringLiteral("==");
};
}

#endif // COMPAREVALIDATOR_H
