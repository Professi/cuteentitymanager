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
        if (!ValidatorFactory::instance.contains(
                    T::staticMetaObject.className())) {
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
