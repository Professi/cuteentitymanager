#ifndef LENGTHVALIDATOR_H
#define LENGTHVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class LengthValidator : public Validator {
    Q_OBJECT
  public:
    LengthValidator();
  protected:
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}
#endif // LENGTHVALIDATOR_H
