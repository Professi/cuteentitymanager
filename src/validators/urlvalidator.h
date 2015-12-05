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
#ifndef URLVALIDATOR_H
#define URLVALIDATOR_H

#include "validator.h"
namespace CuteEntityManager {
class UrlValidator : public Validator {
    Q_OBJECT
  public:
    UrlValidator();
    ErrorMsg validateParam(QVariant value, Param param) const final override;
    QStringList getValidSchemes() const;
    void setValidSchemes(const QStringList &value);

    QString getPattern() const;
    void setPattern(const QString &value);

  protected:
    QString pattern =
        QStringLiteral("/^{schemes}:\\/\\/(([A-Z0-9][A-Z0-9_-]*)(\\.[A-Z0-9][A-Z0-9_-]*)+)/i");
    QStringList validSchemes = {"http", "https"};
};
}

#endif // URLVALIDATOR_H
