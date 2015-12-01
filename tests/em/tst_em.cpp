#include <QString>
#include <QtTest>
#include "entitymanager.h"
#include "databasemigration.h"
#include "../models.h"
class Em : public QObject {
    Q_OBJECT

  public:
    Em();

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

  private:
    CuteEntityManager::EntityManager *e;
    void createRelationTables();
    void deleteRelationTables();
};

Em::Em() {
}

void Em::initTestCase() {
    CuteEntityManager::EntityInstanceFactory::registerClass<Group>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Person>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Article>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Employee>();
    CuteEntityManager::EntityInstanceFactory::registerClass<WorkerGroup>();
    this->e = new CuteEntityManager::EntityManager("QSQLITE",
            ":memory:", "", "", "", "", true, "foreign_keys = ON");
}

void Em::cleanupTestCase() {
    if (this->e) {
        delete this->e;
        this->e = nullptr;
    }
}

void Em::testCheckDuplicates() {
    QSharedPointer<Article> article = QSharedPointer<Article>(new Article(10,
                                      QString("TestItem")));
    QSharedPointer<Entity> entity = article.objectCast<Entity>();
    QVERIFY(this->e->create(entity));
    QSharedPointer<Entity> copy = QSharedPointer<Entity>(article->copy());
    QVERIFY(!this->e->create(copy, true, true));
}

void Em::testBasics() {
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
}

void Em::init() {
    QStringList inits = QStringList() << "Person" << "Group" << "Article";
    QVERIFY2(this->e->startup("emTestA", inits), "Failure");
    auto tableNames = this->e->getSchema()->getTableNames();
    QVERIFY(tableNames.contains("article"));
    QVERIFY(tableNames.contains("person"));
    QVERIFY(tableNames.contains("group"));
    QVERIFY(tableNames.contains("person_groups"));
    QVERIFY(!tableNames.contains("group_persons"));
    QVERIFY(tableNames.contains("cuteentitymanager::databasemigration"));
    auto migrations = this->e->findAll<CuteEntityManager::DatabaseMigration>();
    QCOMPARE(migrations.size(), 1);
    QCOMPARE(migrations.at(0)->getVersion(), QString("emTestA"));
}

void Em::cleanup() {
    auto qb = this->e->getQueryBuilder();
    QVERIFY(this->e->executeQuery(qb->dropTable("person_groups")));
    QVERIFY(this->e->executeQuery(qb->dropTable("group")));
    QVERIFY(this->e->executeQuery(qb->dropTable("person")));
    QVERIFY(this->e->executeQuery(qb->dropTable("article")));
    auto tableNames = this->e->getSchema()->getTableNames();
    QVERIFY(!tableNames.contains("person"));
    QVERIFY(!tableNames.contains("group"));
    QVERIFY(!tableNames.contains("article"));
    QVERIFY(!tableNames.contains("person_groups"));
    QVERIFY(this->e->removeAll("cuteentitymanager::databasemigration"));
}

void Em::testRelationTableCreation() {
    this->createRelationTables();
    auto tableNames = this->e->getSchema()->getTableNames();
    QVERIFY(tableNames.contains("workergroup"));
    QVERIFY(tableNames.contains("employee"));
    QVERIFY(tableNames.contains("workergroup_workers"));
    QVERIFY(!tableNames.contains("group_employee"));
    QVERIFY(!tableNames.contains("employee_workergroups"));
    QVERIFY(!tableNames.contains("employee_groups"));
    QVERIFY(tableNames.contains("cuteentitymanager::databasemigration"));
    auto migrations = this->e->findAll<CuteEntityManager::DatabaseMigration>();
    QCOMPARE(migrations.size(), 2);
    QCOMPARE(migrations.at(1)->getVersion(), QString("emTestB"));
    this->deleteRelationTables();
}

void Em::createRelationTables() {
    QStringList relationTables = QStringList() << "Employee" << "WorkerGroup";
    QVERIFY2(this->e->startup("emTestB", relationTables), "Failure");
}

void Em::deleteRelationTables() {
    auto qb = this->e->getQueryBuilder();
    QVERIFY(this->e->executeQuery(qb->dropTable("workergroup_workers")));
    QVERIFY(this->e->executeQuery(qb->dropTable("employee")));
    QVERIFY(this->e->executeQuery(qb->dropTable("workergroup")));
}

void Em::testFindById() {
    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Patrick", "De",
                               Person::Gender::MALE, "patrick.jpeg", "", "Pat", QDate(2000, 1, 1)));
    auto ent = p.objectCast<Entity>();
    QVERIFY(this->e->create(ent));
    auto id = p->getId();
    QVERIFY(id > -1);
    QVERIFY(this->e->findById(id, p->getClassname()));
}

void Em::testFindId() {
    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Essi", "Sa",
                               Person::Gender::MALE, "essi.jpeg", "", "Essi", QDate(2000, 1, 1)));
    auto ent = p.objectCast<Entity>();
    QVERIFY(this->e->create(ent));
    auto entity = QSharedPointer<Entity>(p->copy());
    auto foundId = this->e->findId(entity);
    QVERIFY(foundId  > -1 && foundId == ent->getId());
}

void Em::testHasChanged() {
    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Jelena", "Fl",
                               Person::Gender::MALE, "max.jpeg", "", "Maxi", QDate(2000, 1, 1)));
    auto ent = p.objectCast<Entity>();
    QVERIFY(this->e->create(ent));
    p->setFirstName("Laura");
    p->setFamilyName("Musterfrau");
    p->setBirthday(QDate(200, 1, 2));
    QVERIFY(this->e->hasChanged(ent));
}

void Em::testValidate() {
    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Patrick", "Pe",
                               Person::Gender::MALE, "patrick2.jpeg", "", "Maxi", QDate(2000, 1, 1)));
    auto ent = p.objectCast<Entity>();
    QVERIFY(this->e->validate(ent));
    p->setFirstName("M");
    QVERIFY(!this->e->validate(ent) && ent->getErrors().size() == 1);
    p->setBirthday(QDate(2030, 10, 10));
    QVERIFY(!this->e->validate(ent) && ent->getErrors().size() == 2);
}

void Em::testRelations() {
    QSharedPointer<Person> p1 = QSharedPointer<Person>(new Person("Lucien", "We",
                                Person::Gender::MALE, "lucien.jpeg", "", "Luc", QDate(2000, 1, 1)));
    QSharedPointer<Person> p2 = QSharedPointer<Person>(new Person("Janine", "Musterfrau",
                                Person::Gender::FEMALE, "janine.jpeg", "", "", QDate(2000, 1, 1)));
    QSharedPointer<Person> p3 = QSharedPointer<Person>(new Person("Fenja", "Sey.",
                                Person::Gender::FEMALE, "fenja.jpeg", "", "Lotta", QDate(1990, 1, 1)));
    QSharedPointer<Group> g = QSharedPointer<Group>(new Group());
    g->setName("TestGroup");
    g->setLeader(p1);
    g->setPersons({p1});
    auto gEnt = g.objectCast<Entity>();
    auto pEnt = p3.objectCast<Entity>();
    QVERIFY(this->e->save(gEnt));
    QVERIFY(p1->getId() > -1);
    QVERIFY(p1->getMaintainedGroups().size() > 0);
    QVERIFY(p1->getGroups().size() > 0);
    g->addPerson(p2);
    g->setName("TestGroupExtended");
    QVERIFY(this->e->save(gEnt));
    p3->setGroups({g});
    QVERIFY(this->e->save(pEnt, true, true));
    QVERIFY(g->getPersons().size() == 3);
    QList<QSharedPointer<Group>> groups;
    p3->setGroups(groups);
    QVERIFY(this->e->save(pEnt, true, true));
    this->e->refresh(gEnt);
    QVERIFY(g->getPersons().size() == 2);
    auto firstPerson = g->getPersons().first();
    g->removePerson(firstPerson);
    QVERIFY(this->e->save(gEnt, true, true));
    auto entityFp = firstPerson.objectCast<Entity>();
    this->e->refresh(entityFp);
    QVERIFY(firstPerson->getGroups().size() == 0 && g->getPersons().size() == 1);
}

QTEST_APPLESS_MAIN(Em)

#include "tst_em.moc"
