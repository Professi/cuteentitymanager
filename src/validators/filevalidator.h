/*
 * Copyright (C) 2015 Christian Ehringfeld <c.ehringfeld@t-online.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FILEVALIDATOR_H
#define FILEVALIDATOR_H
#include "validator.h"
#include <QFileInfo>
namespace CuteEntityManager {
class FileValidator : public Validator {
    Q_OBJECT
  public:
    FileValidator();
  protected:
    virtual ErrorMsg validateParam(QVariant value, Param param) const override;
    virtual ErrorMsg validateMIMEType(const QFileInfo &file,
                                      const Param &param) const;
    virtual ErrorMsg validateExtension(const QFileInfo &file,
                                       const Param &param) const;
};
}
#endif // FILEVALIDATOR_H
