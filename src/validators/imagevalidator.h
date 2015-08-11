#ifndef IMAGEVALIDATOR_H
#define IMAGEVALIDATOR_H
#include "filevalidator.h"
namespace CuteEntityManager {
class ImageValidator : public FileValidator {
    Q_OBJECT
  public:
    ImageValidator();
    ErrorMsg validateParam(QVariant value, Param param) const final override;
    virtual ErrorMsg validateImage(QVariant value, Param param) const;
};
}

#endif // IMAGEVALIDATOR_H
