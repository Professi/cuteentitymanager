#ifndef EXISTVALIDATOR_H
#define EXISTVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class ExistValidator : public Validator {
    Q_OBJECT
  public:
    ExistValidator();
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}
#endif // EXISTVALIDATOR_H
