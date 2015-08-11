#ifndef DEFAULTVALIDATOR_H
#define DEFAULTVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class DefaultValidator : public Validator {
    Q_OBJECT
  public:
    DefaultValidator();
  protected:
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}

#endif // DEFAULTVALIDATOR_H
