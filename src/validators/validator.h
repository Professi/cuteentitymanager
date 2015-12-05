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
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>
#include <QHash>
#include "param.h"
#include "errormsg.h"
namespace CuteEntityManager {
class Validator : public QObject {
    Q_OBJECT
  public:
    Validator();
    virtual ~Validator();
    static const QHash<QString, QString> builtInValidators();
    virtual QList<ErrorMsg> validate(QVariant value, QList<Param> params) const;
    QString generateErrorMsg(ErrorMsg msg);

  protected:
    virtual ErrorMsg validateParam(QVariant value, Param param) const = 0;
};
}
#endif // VALIDATOR_H
