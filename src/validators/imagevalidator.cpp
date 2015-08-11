#include "imagevalidator.h"
#ifdef QT_GUI_LIB
#include <QImage>
#endif
using namespace CuteEntityManager;
ImageValidator::ImageValidator() : FileValidator() {
}

ErrorMsg ImageValidator::validateParam(QVariant value, Param param) const {
    ErrorMsg msg = FileValidator::validateParam(value, param);
    if (msg.getErrorMsg().isEmpty()) {
        msg = this->validateImage(value, param);
    }
    return msg;
}

ErrorMsg ImageValidator::validateImage(QVariant value, Param param) const {
#ifdef QT_GUI_LIB
    //isImage
    QImage img = QImage(value.toString());
    if (!img.isNull()) {
        if (param.getName() == "minWidth"
                && img.width() < param.getValue().toLongLong()) {
            ErrorMsg(param.getName(),
                     "The image " + value.toString() +
                     " is too smal. The width cannot be smaller than " + param.getValue().toString()
                     + ".");
        } else if (param.getName() == "maxWidth"
                   && img.width() > param.getValue().toLongLong()) {
            ErrorMsg(param.getName(),
                     "The image " + value.toString() +
                     " is too smal. The width cannot be larger than " + param.getValue().toString() +
                     ".");
        } else if (param.getName() == "minHeight"
                   && img.height() < param.getValue().toLongLong()) {
            ErrorMsg(param.getName(),
                     "The image " + value.toString() +
                     " is too smal. The height cannot be smaller than " + param.getValue().toString()
                     + ".");
        } else if (param.getName() == "maxHeight"
                   && img.height() > param.getValue().toLongLong()) {
            ErrorMsg(param.getName(),
                     "The image " + value.toString() +
                     " is too smal. The height cannot be larger than " + param.getValue().toString()
                     + ".");
        }
    } else {
        return ErrorMsg("", "The file " + value.toString() + " is not a valid image.");
    }
#else
    Q_UNUSED(value)
    Q_UNUSED(param)
#endif
    return ErrorMsg();
}
