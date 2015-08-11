#ifndef REQUIREDVALIDATOR_H
#define REQUIREDVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class RequiredValidator : public Validator {
    Q_OBJECT
  public:
    RequiredValidator();
  protected:
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}

#endif // REQUIREDVALIDATOR_H
