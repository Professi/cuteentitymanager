#include "entityinstancefactory.h"
#include "entity.h"
#include <QMetaType>
using namespace CuteEntityManager;
EntityInstanceFactory::EntityInstanceFactory() {

}

Entity *EntityInstanceFactory::createInstance(const char *className) {
    return EntityInstanceFactory::createInstance(QMetaType::type(className));
}

Entity *EntityInstanceFactory::createInstance(const QString &className) {
    return EntityInstanceFactory::createInstance(className.toUtf8().constData());
}

Entity *EntityInstanceFactory::createInstance(int id) {
    Entity *e = 0;
    if (id != -1) {
        e = static_cast<Entity *>(QMetaType::create(id));
    }
    return e;
}

Entity *EntityInstanceFactory::createInstance(const char *className, const QHash<QString, QVariant> &attributes) {
    Entity *e = EntityInstanceFactory::createInstance(className);
    EntityInstanceFactory::setAttributes(e, attributes);
    return e;
}

Entity *EntityInstanceFactory::setAttributes(Entity *e, const QHash<QString, QVariant> &attributes,
        QHash<QString, QMetaProperty> metaprops) {
    if (e) {
        auto iterator = attributes.constBegin();
        while (iterator != attributes.constEnd()) {
            if (metaprops.contains(iterator.key())) {
                QMetaProperty prop = metaprops.value(iterator.key());
                if (!prop.isWritable() && !prop.write(e, iterator.value())) {
                    qDebug() << prop.name() << "on Entity" << e->getClassname() << "not writeable!";
                }
            }
            ++iterator;
        }
    }
    return e;
}

Entity *EntityInstanceFactory::setAttributes(Entity *e, const QHash<QString, QVariant> &attributes) {
    auto metaprops = e->getMetaProperties();
    return EntityInstanceFactory::setAttributes(e, attributes, metaprops);
}
