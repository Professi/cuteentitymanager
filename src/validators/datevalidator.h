#ifndef DATEVALIDATOR_H
#define DATEVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class DateValidator : public Validator {
    Q_OBJECT
  public:
    DateValidator();
  protected:
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}

#endif // DATEVALIDATOR_H
