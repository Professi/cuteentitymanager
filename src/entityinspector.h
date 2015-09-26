#ifndef ENTITYINSPECTOR_H
#define ENTITYINSPECTOR_H
#include <QString>
#include <QHash>
#include "entity.h"
#include "entityhelper.h"
#include "entityinstancefactory.h"
#include "logger.h"

namespace CuteEntityManager {

/**
 * @brief The EntityInspector class
 * @todo verify Mappings
 */
class EntityInspector {
  public:
    EntityInspector();
    ~EntityInspector();
    bool checkRegisteredEntities();
    bool checkEntity(QString name);

  private:
    Entity *instantiateEntity(const QString name, QString &msg);
    bool verifyRelations(Entity *&entity, QString &msg);
    void verifyTransientAttributes(Entity *&entity, QString &msg);
    bool checkRelation(const QVariant &entity, const Relation &r, QString &msg,
                       const QMetaProperty &property) const;
    bool checkPrimaryKey(Entity *&entity, QString &msg);
    void verifyBlobAttributes(Entity *&entity, QString &msg);
    void checkMetaProperties(QHash<QString, QMetaProperty> &metaProperties,
                             QString &msg, bool &ok, QHash<QString, Relation> &relations);
    void initLogger();
    Logger *logger = nullptr;
};
}
#endif // ENTITYINSPECTOR_H
