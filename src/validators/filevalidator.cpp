#include "filevalidator.h"
#include <QFileInfo>
#include <QMimeType>
#include <QMimeDatabase>
using namespace CuteEntityManager;
FileValidator::FileValidator() : Validator() {

}

/**
 * @brief FileValidator::validateParam
 * @param value must be the absolute FilePath
 * @param param
 * @return
 */
ErrorMsg FileValidator::validateParam(QVariant value, Param param) const {
    QString fileName = value.toString();
    if (!fileName.isEmpty()) {
        QFileInfo file = QFileInfo(value.toString());
        if (param.getName() == "mimeTypes") {
            return this->validateMIMEType(file, param);
        } else if (param.getName() == "extensions") {
            return this->validateExtension(file, param);
        } else if (param.getName() == "minSize"
                   && file.size() < param.getValue().toLongLong()) {
            return ErrorMsg(param.getName(),
                            "The file <property> is too small. Its size cannot be smaller than " +
                            param.getValue().toString() + " bytes.");

        } else if (param.getName() == "maxSize") {
            return ErrorMsg(param.getName(),
                            "The file <property> is too big. Its size cannot exceed " +
                            param.getValue().toString() + " bytes.");
        }
    }
    return ErrorMsg();
}

ErrorMsg FileValidator::validateMIMEType(const QFileInfo &file,
        const Param &param) const {
    QMimeDatabase mimeDatabase;
    QMimeType mimeType = mimeDatabase.mimeTypeForFile(file);
    if (param.getValue().canConvert<QStringList>()) {
        QStringList list = param.getValue().toStringList();
        for (int i = 0; i < list.size(); ++i) {
            if (mimeType.inherits(list.at(i))) {
                return ErrorMsg();
            }
        }
        return ErrorMsg(param.getName(),
                        "Only files with these MIME types are allowed: " + list.join(", ") + ".");
    } else {
        if (!mimeType.inherits(param.getValue().toString())) {
            return ErrorMsg(param.getName(),
                            "Only files with this MIME type are allowed: " +
                            param.getValue().toString() + ".");
        }
    }
    return ErrorMsg();
}

ErrorMsg FileValidator::validateExtension(const QFileInfo &file,
        const Param &param) const {
    if (param.getValue().canConvert<QStringList>()) {
        QStringList list = param.getValue().toStringList();
        for (int i = 0; i < list.size(); ++i) {
            if (file.completeSuffix().contains(list.at(i))) {
                return ErrorMsg();
            }
        }
        return ErrorMsg(param.getName(),
                        "Only files with these extension types are allowed: " + list.join(", "));
    } else {
        if (!file.completeSuffix().contains(param.getValue().toString())) {
            return ErrorMsg(param.getName(),
                            "Only files with this extension type are allowed: " +
                            param.getValue().toString() + ".");
        }
    }
    return ErrorMsg();
}

