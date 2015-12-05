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
#ifndef NUMBERVALIDATOR_H
#define NUMBERVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class NumberValidator : public Validator {
    Q_OBJECT
  public:
    NumberValidator();
  protected:
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}
#endif // NUMBERVALIDATOR_H
