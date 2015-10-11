#include <QString>
#include <QtTest>
#include "entitymanager.h"
#include "databasemigration.h"
#include "../models.h"
class Tables : public QObject {
    Q_OBJECT

  public:
    Tables();

  private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testStartup();
//    void init();
//    void cleanup();
  private:
    CuteEntityManager::EntityManager *e;
};

Tables::Tables() {
}

void Tables::initTestCase() {
    CuteEntityManager::EntityInstanceFactory::registerClass<Group>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Person>();
    this->e = new CuteEntityManager::EntityManager("QSQLITE",
            ":memory:", "", "", "", "", true, "foreign_keys = ON");
}

void Tables::cleanupTestCase() {
//    if (this->e) {
//        delete this->e;
//        this->e = nullptr;
//    }
}

void Tables::testStartup() {
    QStringList inits = QStringList() << "Person" << "Group";
    QVERIFY2(this->e->startup("test0.1", inits), "Failure");
    auto tableNames = this->e->getSchema()->getTableNames();
    QVERIFY(tableNames.contains("person"));
    QVERIFY(tableNames.contains("group"));
    QVERIFY(tableNames.contains("group_persons"));
    QVERIFY(tableNames.contains("cuteentitymanager::databasemigration"));
    auto migrations = this->e->findAll<CuteEntityManager::DatabaseMigration>();
    QCOMPARE(migrations.size(), 1);
    QCOMPARE(migrations.at(0)->getVersion(), QString("test0.1"));
}

QTEST_APPLESS_MAIN(Tables)

#include "tst_tables.moc"
