#ifndef NUMBERVALIDATOR_H
#define NUMBERVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class NumberValidator : public Validator {
    Q_OBJECT
  public:
    NumberValidator();
  protected:
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}
#endif // NUMBERVALIDATOR_H
