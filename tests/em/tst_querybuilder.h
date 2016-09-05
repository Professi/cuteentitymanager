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
    void testFindByAttributesManyToManyResolve();
    void testFindByAttributesOneToManyResolve();
    void testFindByAttributesOneToOneResolve();
    void testFindByAttributesManyToOneResolve();
    void testFindByAttributesSuperClassAttribute();
    void testQueryBuilderCount();
    void testQueryBuilder();
    void testQueryBuilderEntityInheritance();
    void testQueryBuilderEntityInheritanceWithoutJoin();
    void testQueryBuilderArbitraryOperator();
    void testQueryBuilderJoins();
    void testQueryBuilderSingleAttributeOr();
    void testQueryBuilderManyToOneRelationAttribute();
    void testQueryBuilderManyToManyRelationAttribute();
    void testEnum();
    void testRefresh();

  private:
    CuteEntityManager::EntityManager *e;
};
#endif // TST_QUERYBUILDER

