#ifndef UNIQUEVALIDATOR_H
#define UNIQUEVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class UniqueValidator : public Validator {
    Q_OBJECT
  public:
    UniqueValidator();
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}
#endif // UNIQUEVALIDATOR_H
