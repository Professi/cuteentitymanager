#ifndef TST_QUERYBUILDER
#define TST_QUERYBUILDER
#include <QString>
#include <QtTest>
#include "entitymanager.h"
#include "databasemigration.h"
#include "../models.h"

class QuerybuilderTest : public QObject {
    Q_OBJECT

  private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testFindByAttributes();
    void testFindByAttributesManyToOneRelation();
    void testFindByAttributesManyToOneRelationAttribute();
    void testFindByAttributesManyToManyRelation();
    void testFindByAttributesManyToManyRelationWithList();
    void testFindByAttributesManyToManyRelationAttribute();
    void testQueryBuilder();
  private:
    CuteEntityManager::EntityManager *e;
};
#endif // TST_QUERYBUILDER

