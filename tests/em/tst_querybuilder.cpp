#include "tst_querybuilder.h"
#include <QDebug>

void QuerybuilderTest::initTestCase() {
    CuteEntityManager::EntityInstanceFactory::registerClass<Group>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Person>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Employee>();
    CuteEntityManager::EntityInstanceFactory::registerClass<WorkerGroup>();
    this->e = new CuteEntityManager::EntityManager("QSQLITE", ":memory:", "", "", "", "",
            true, "foreign_keys = ON", false);
    QStringList inits = QStringList() << "Person" << "Group" << "Employee" << "WorkerGroup";
    QVERIFY2(this->e->startup("queryBuilderTest", inits), "Failure");
    QSharedPointer<Person> p1 = QSharedPointer<Person>(new Person("Lucien", "We",
                                Person::Gender::MALE, "Luc", QDate(1995, 2, 4)));
    QSharedPointer<Employee> p2 = QSharedPointer<Employee>(new Employee(11, "Janine",
                                  "Musterfrau",
                                  Person::Gender::FEMALE, "", QDate(1992, 8, 5), "B"));
    QSharedPointer<Employee> p3 = QSharedPointer<Employee>(new Employee(42, "Fenja", "Sey.",
                                  Person::Gender::FEMALE, "Lotta", QDate(1990, 11, 11), "A"));
    QSharedPointer<Person> p4 = QSharedPointer<Person>(new Person("Fenja", "Neu",
                                Person::Gender::FEMALE, "Fenni", QDate(1980, 5, 30)));
    QSharedPointer<Employee> p5 = QSharedPointer<Employee>(new Employee(90, "Milan", "Mes.",
                                  Person::Gender::MALE, "", QDate(1994, 3, 27), "D"));
    QSharedPointer<Person> p6 = QSharedPointer<Person>(new Person("Kristina", "Zero",
                                Person::Gender::FEMALE, "", QDate(1996, 5, 17)));
    QSharedPointer<Group> g = QSharedPointer<Group>(new Group("Group Psy"));
    QSharedPointer<Group> g2 = QSharedPointer<Group>(new Group("Group Health"));
    QSharedPointer<Group> g3 = QSharedPointer<Group>(new Group("Group ABC"));
    g->setLeader(p1);
    g3->setLeader(p3);
    g3->setPersons({p3});
    g->setPersons({p1, p2, p4});
    g2->setLeader(p3);
    g2->setPersons({p3});
    QSharedPointer<WorkerGroup> wg = QSharedPointer<WorkerGroup>(new
                                     WorkerGroup("Taskforce P&H", 50));
    wg->addWorker(p2);
    wg->addWorker(p3);
    try {
        QVERIFY(this->e->save(p5));
        QVERIFY(this->e->save(g));
        QVERIFY(this->e->save(wg));
        QVERIFY(this->e->save(g2));
        QVERIFY(this->e->save(p6));
        QVERIFY(this->e->save(g3));
    } catch(QString s) {
        qWarning() << s;
    }
}

void QuerybuilderTest::cleanupTestCase() {
    auto qb = this->e->getQueryBuilder();
    QVERIFY(this->e->executeQuery(qb->dropTable("workergroup_workers")));
    QVERIFY(this->e->executeQuery(qb->dropTable("employee")));
    QVERIFY(this->e->executeQuery(qb->dropTable("workergroup")));
    QVERIFY(this->e->executeQuery(qb->dropTable("person_groups")));
    QVERIFY(this->e->executeQuery(qb->dropTable("group")));
    QVERIFY(this->e->executeQuery(qb->dropTable("person")));
    QVERIFY(this->e->removeAll("cuteentitymanager::databasemigration"));
    if (this->e) {
        delete this->e;
        this->e = nullptr;
    }
}

void QuerybuilderTest::testFindByAttributes() {
    QHash<QString, QVariant> attributes;
    attributes["persNumber"] = 42;
    QSharedPointer<Employee> p = e->findEntityByAttributes<Employee>(attributes, true);
    QVERIFY(p);
    QCOMPARE(p->getNickName(), QString("Lotta"));
}

void QuerybuilderTest::testFindByAttributesManyToManyResolve() {
    QHash<QString, QVariant> attributes;
    attributes["persNumber"] = 42;
    QSharedPointer<Employee> p = e->findEntityByAttributes<Employee>(attributes, true);
    QVERIFY(p);
    QCOMPARE(p->getNickName(), QString("Lotta"));
    QCOMPARE(p->getGroups().size(), 2);
    QVERIFY(p->getGroups().first());
    QVERIFY(p->getGroups().first()->getPersons().last());
    QCOMPARE(p->getGroups().first()->getPersons().last()->getFamilyName(), QString("Sey."));
}

void QuerybuilderTest::testFindByAttributesOneToManyResolve() {
    QHash<QString, QVariant> attributes;
    attributes["persNumber"] = 42;
    QSharedPointer<Employee> p = e->findEntityByAttributes<Employee>(attributes, true);
    QVERIFY(p);
    QCOMPARE(p->getMaintainedGroups().size(), 2);
}

void QuerybuilderTest::testFindByAttributesOneToOneResolve() {
}

void QuerybuilderTest::testFindByAttributesManyToOneResolve() {
    QHash<QString, QVariant> attributes;
    attributes["name"] = QString("Group Health");
    QSharedPointer<Group> g = this->e->findEntityByAttributes<Group>(attributes, true);
    QVERIFY(g->getLeader());
    QCOMPARE(g->getLeader()->getFirstName(), QString("Fenja"));
    QCOMPARE(g->getLeader()->getFamilyName(), QString("Sey."));
}

void QuerybuilderTest::testFindByAttributesSuperClassAttribute() {
    auto qb = e->getQueryBuilder();
    Query q = Query();
    q.appendWhere(q.equal(qb, "nickName", QString("Lotta")));
    QList<QSharedPointer<Employee>> list = e->find<Employee>(q, true);
    QCOMPARE(list.size(), 1);
    QCOMPARE(list.at(0)->getPersNumber(), (unsigned long long)42);
}

void QuerybuilderTest::testQueryBuilderCount() {
    auto qb = e->getQueryBuilder();
    Query q = Query();
    q.appendWhere(q.equal(qb, "gender", (int) Person::Gender::FEMALE));
    q.appendFrom("person");
    QCOMPARE(this->e->count(q), (quint32)4);
}

void QuerybuilderTest::testQueryBuilder() {
    auto qb = this->e->getQueryBuilder();
    Query q = Query();
    q.appendWhere(q.like(qb, QString("firstName"), QString("Fenj"),
                         JokerPosition::BEHIND));
    q.setLimit(10);
    QList<QSharedPointer<Person>> list = this->e->find<Person>(q);
    QCOMPARE(list.size(), 2);
}

void QuerybuilderTest::testQueryBuilderEntityInheritance() {
    auto qb = e->getQueryBuilder();
    QSharedPointer<Employee> emp = QSharedPointer<Employee>(new Employee());
    Query q = Query();
    q.appendJoins(q.joinBaseClasses(qb, emp));
    try {
        QList<QSharedPointer<Employee>> list = this->e->find<Employee>(q);
        QCOMPARE(list.size(), 3);
    } catch(QString e) {
        qWarning() << e;
        QFAIL("Exception");
    }
}

void QuerybuilderTest::testQueryBuilderEntityInheritanceWithoutJoin() {
    Query q = Query();
    try {
        QList<QSharedPointer<Employee>> list = this->e->find<Employee>(q, true);
        QCOMPARE(list.size(), 3);
    } catch(QString e) {
        qWarning() << e;
        QFAIL("Exception");
    }
}

void QuerybuilderTest::testQueryBuilderArbitraryOperator() {
    auto qb = e->getQueryBuilder();
    Query q = Query();
    q.appendWhere(q.arbitraryOperator(qb, "<", "birthday",
                                      QDate(1991, 10, 10)));
    q.setDistinct(true);
    q.appendOrderBy(OrderBy(QString("birthday"), Direction::SORT_DESC));
    q.setLimit(10);
    QList<QSharedPointer<Person>> list = this->e->find<Person>(q, true);
    QCOMPARE(list.size(), 2);
    QCOMPARE(list.at(0)->getFirstName(), QString("Fenja"));
    QCOMPARE(list.at(0)->getFamilyName(), QString("Sey."));
    QCOMPARE(list.at(1)->getFirstName(), QString("Fenja"));
    QCOMPARE(list.at(1)->getFamilyName(), QString("Neu"));
}

void QuerybuilderTest::testQueryBuilderJoins() {
    auto qb = e->getQueryBuilder();
    Query q = Query();
    q.appendWhere(q.equal(qb, "firstName", "Milan"));
    q.appendJoin(Join("person", "person.id = employee.id"));
    QList<QSharedPointer<Employee>> list = this->e->find<Employee>(q, false);
    QCOMPARE(list.size(), 1);
    QCOMPARE(list.at(0)->getFirstName(), QString("Milan"));
    QCOMPARE(list.at(0)->getFamilyName(), QString("Mes."));
}

void QuerybuilderTest::testQueryBuilderSingleAttributeOr() {
    auto qb = e->getQueryBuilder();
    Query q = Query();
    q.appendWhere(q.equal(qb, "nickName", QString("Lotta")));
    q.appendWhere(q.orOperator(qb));
    q.appendWhere(q.equal(qb, "nickName", QString("Fenni")));
    QList<QSharedPointer<Person>> list = e->find<Person>(q, true);
    QCOMPARE(list.size(), 2);
}

void QuerybuilderTest::testQueryBuilderManyToOneRelationAttribute() {
    auto qb = e->getQueryBuilder();
    Query q = Query();
    q.appendJoinWith("leader");
    q.appendOrderBy("name", Direction::SORT_DESC);
    q.appendWhere(q.equal(qb, "leader.firstName", QString("Fenja")));
    QList<QSharedPointer<Group>> groupList = e->find<Group>(q, false, false);
    QCOMPARE(groupList.size(), 2);
    QCOMPARE(groupList.at(0)->getName(), QString("Group Health"));
    QCOMPARE(groupList.at(0)->getPersons().size(), 1);
}

void QuerybuilderTest::testQueryBuilderManyToManyRelationAttribute() {
    auto qb = e->getQueryBuilder();
    Query q = Query();
    q.appendJoinWith("persons");
    q.appendWhere(q.equal(qb, "persons.firstName", QString("Janine")));
    QList<QSharedPointer<Group>> groupList = e->find<Group>(q, false);
    QCOMPARE(groupList.size(), 1);
    QCOMPARE(groupList.at(0)->getName(), QString("Group Psy"));
    QCOMPARE(groupList.at(0)->getPersons().size(), 3);
}

void QuerybuilderTest::testEnum()
{
      auto qb = e->getQueryBuilder();
       Query q = Query();
        QVariant var;
        var.setValue<Person::Gender>(Person::Gender::FEMALE);
        q.appendWhere(q.equal(qb, "gender", var.toInt()));
        QList<QSharedPointer<Person>> females = e->find<Person>(q, false);
        QCOMPARE(females.size(), 4);
        QCOMPARE(females.first()->getGender(), Person::Gender::FEMALE);
}

void QuerybuilderTest::testRefresh() {
    e->clearCache();
    auto persons = e->findAll<Person>(false);
    QCOMPARE(persons.first()->getGroups().size(), 0);
    QHash<QString, QVariant> attributes;
    attributes["name"] = QString("Group Health");
    QSharedPointer<Group> g = this->e->findEntityByAttributes<Group>(attributes, false,
                              false);
    QCOMPARE(g->getPersons().count(), 0);
    e->refresh(g, true);
    QCOMPARE(g->getPersons().count(), 1);
}
