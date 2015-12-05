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
#ifndef VALIDATORATTRIBUTE_H
#define VALIDATORATTRIBUTE_H
#include <QString>
#include <QStringList>
#include "param.h"
namespace CuteEntityManager {
class ValidationRule {
  public:
    ValidationRule();
    explicit ValidationRule(QString validatorName, QString attributeName,
                            QList<Param> params = QList<Param>());
    explicit ValidationRule(QString validatorName, QString attributeName,
                            Param param);
    explicit ValidationRule(QString validatorName, QStringList attributeNames,
                            QList<Param> params = QList<Param>());
    explicit ValidationRule(QString validatorName, QStringList attributeNames,
                            Param param);
    explicit ValidationRule(QString validatorName, QString attributeName,
                            QString paramName, QString paramValue);
    explicit ValidationRule(QString validatorName, QString attributeName,
                            QString paramName1, QVariant paramValue1, QString paramName2,
                            QVariant paramValue2);
    explicit ValidationRule(QString validatorName, QStringList attributeNames,
                            QString paramName, QVariant paramValue = QVariant());
    explicit ValidationRule(QString validatorName, QStringList attributeNames,
                            QString paramName1, QVariant paramValue1, QString paramName2,
                            QVariant paramValue2);
    ~ValidationRule();
    QString getValidatorName() const;
    void setValidatorName(const QString &value);

    QStringList getAttributes() const;
    void setAttributes(const QStringList &value);

    QList<Param> getParams() const;
    void setParams(const QList<Param> &value);

  private:
    QString validatorName;
    QStringList attributes;
    QList<Param> params;
};
}


#endif // VALIDATORATTRIBUTE_H
