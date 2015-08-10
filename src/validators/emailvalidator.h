#ifndef EMAILVALIDATOR_H
#define EMAILVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class EmailValidator : public Validator {
    Q_OBJECT
  public:
    EmailValidator();
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}
#endif // EMAILVALIDATOR_H
