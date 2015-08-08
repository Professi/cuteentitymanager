#ifndef DEFAULTVALIDATOR_H
#define DEFAULTVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class ErrorMsg;
class DefaultValidator : public Validator {
    Q_OBJECT
  public:
    DefaultValidator();
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}

#endif // DEFAULTVALIDATOR_H
