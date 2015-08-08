#ifndef VALIDATORFACTORY_H
#define VALIDATORFACTORY_H
#include <QString>
#include <QHash>
namespace CuteEntityManager {
class Validator;
class ValidatorFactory {
  public:
    static void registerClasses();
    static Validator *createValidator(QString shortname);
    template<typename T>
    static void registerClass() {
        if (!ValidatorFactory::instance.contains(
                    T::staticMetaObject.className())) {
            ValidatorFactory::instance.insert( T::staticMetaObject.className(),
                                               &constructorHelper<T> );
        }
    }

    static Validator *createObject( const QByteArray &className) {
        Constructor constructor = ValidatorFactory::instance.value(className);
        if ( constructor == nullptr ) {
            return nullptr;
        }
        return (*constructor)();
    }
    typedef Validator *(*Constructor)();
    template<typename T>
    static Validator *constructorHelper() {
        return new T();
    }
    static QHash<QByteArray, Constructor> instance;

  protected:
    ValidatorFactory();
};
}

#endif // VALIDATORFACTORY_H
