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
    void testBasics();
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
    CuteEntityManager::EntityInstanceFactory::registerClass<Article>();
    this->e = new CuteEntityManager::EntityManager("QSQLITE",
            ":memory:", "", "", "", "", true, "foreign_keys = ON");
}

void Tables::cleanupTestCase() {
    if (this->e) {
        delete this->e;
        this->e = nullptr;
    }
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

void Tables::testBasics() {
    this->e->createTable("Article");
    QVERIFY(this->e->getSchema()->getTableNames().contains("article"));
    QSharedPointer<Article> article = QSharedPointer<Article>(new Article(10,
                                      QString("TestItem")));
    QSharedPointer<Entity> entity = article.objectCast<Entity>();
    QVERIFY(this->e->create(entity));
    article->setPrice(20);
    article->setName("NewTestItem");
    QVERIFY(this->e->save(entity));
    QHash<QString, QVariant> attrs = QHash<QString, QVariant>();
    attrs.insert("price", 20);
    attrs.insert("name", "NewTestItem");
    QSharedPointer<Article> article2 = this->e->findEntityByAttributes<Article>
                                       (attrs);
    QVERIFY(article2);
    entity = article2.objectCast<Entity>();
    QVERIFY(this->e->remove(entity));
    QCOMPARE(this->e->count("article"), (quint8)0);
    this->e->getDb()->exec(this->e->getQueryBuilder()->dropTable("article"));
    QVERIFY(!this->e->getSchema()->getTableNames().contains("article"));
}

QTEST_APPLESS_MAIN(Tables)

#include "tst_tables.moc"
