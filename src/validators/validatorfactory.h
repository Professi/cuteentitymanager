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
#ifndef VALIDATORFACTORY_H
#define VALIDATORFACTORY_H
#include <QString>
#include <QHash>
#include <QSharedPointer>
namespace CuteEntityManager {
class Validator;
class ValidatorFactory {
  public:
    static void registerClasses();
    static Validator *createValidator(const QString &shortname);
    template<typename T>
    static void registerClass() {
        if (!ValidatorFactory::instance.contains(T::staticMetaObject.className())) {
            ValidatorFactory::instance.insert( T::staticMetaObject.className(),
                                               &constructorHelper<T> );
        }
    }

    static Validator *createObject( const QByteArray &className);

    static QSharedPointer<Validator> getValidatorObject(const QString &shortname);

    typedef Validator *(*Constructor)();
    template<typename T>
    static Validator *constructorHelper() {
        return new T();
    }
    static QHash<QByteArray, Constructor> instance;
    static QHash<QString, QSharedPointer<Validator>> validatorInstances;

  protected:
    ValidatorFactory();
};
}

#endif // VALIDATORFACTORY_H
