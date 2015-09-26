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
 * This class can check entities for errors.
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
    void checkRelationTypos(const QString &name, const Relation &r, QString &msg,
                            bool &ok);
    void checkRelationMappings(QMetaProperty &property, const Relation &r,
                               QString &msg, bool &ok);
    bool checkPrimaryKey(Entity *&entity, QString &msg);
    void verifyBlobAttributes(Entity *&entity, QString &msg);
    void checkMetaProperties(QHash<QString, QMetaProperty> &metaProperties,
                             QString &msg, bool &ok, QHash<QString, Relation> &relations);
    void initLogger();
    Logger *logger = nullptr;
};
}
#endif // ENTITYINSPECTOR_H
