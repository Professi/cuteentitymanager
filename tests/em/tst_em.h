#ifndef TST_EM
#define TST_EM
#include <QString>
#include <QtTest>
#include <QSqlIndex>
#include "entitymanager.h"
#include "databasemigration.h"
#include "../models.h"

class EmTest : public QObject {
    Q_OBJECT

  private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCheckDuplicates();
    void testBasics();
    void init();
    void cleanup();
    void testFindById();
    void testFindId();
    void testHasChanged();
    void testValidate();
    void testRelations();
    void testRelationTableCreation();
    void testInheritedRelations();
    void testDatabaseMigrationTable();
    void testTableCreation();

  private:
    CuteEntityManager::EntityManager *e;
    void createRelationTables();
    void deleteRelationTables();
    void containsColumn(QHash<QString, QSharedPointer<QSqlField>> &columns, QString name,
                        QVariant::Type type = QVariant::UserType, QString tableName = "", bool pk = false);
};
#endif // TST_EM

