#include "tst_querybuilder.h"

void QuerybuilderTest::initTestCase() {
    CuteEntityManager::EntityInstanceFactory::registerClass<Group>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Person>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Article>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Employee>();
    CuteEntityManager::EntityInstanceFactory::registerClass<WorkerGroup>();
    this->e = new CuteEntityManager::EntityManager("QSQLITE",
            ":memory:", "", "", "", "", true, "foreign_keys = ON", false);
    QStringList inits = QStringList() << "Person" << "Group" << "Employee" << "WorkerGroup";
    QVERIFY2(this->e->startup("queryBuilderTest", inits), "Failure");
    QSharedPointer<Person> p1 = QSharedPointer<Person>(new Person("Lucien", "We",
                                Person::Gender::MALE, "lucien.jpeg", "", "Luc", QDate(1995, 2, 4)));
    QSharedPointer<Employee> p2 = QSharedPointer<Employee>(new Employee(11, "Janine",
                                  "Musterfrau",
                                  Person::Gender::FEMALE, "janine.jpeg", "", "", QDate(1992, 8, 5), "B"));
    QSharedPointer<Employee> p3 = QSharedPointer<Employee>(new Employee(42, "Fenja", "Sey.",
                                  Person::Gender::FEMALE, "fenja.jpeg", "", "Lotta", QDate(1990, 11, 11), "A"));
    QSharedPointer<Person> p4 = QSharedPointer<Person>(new Person("Fenja", "Neu",
                                Person::Gender::FEMALE, "fenja2.jpeg", "", "Fenni", QDate(1980, 5, 30)));
    QSharedPointer<Group> g = QSharedPointer<Group>(new Group("Group Psy"));
    QSharedPointer<Group> g2 = QSharedPointer<Group>(new Group("Group Health"));
    g->setLeader(p1);
    g->setPersons({p1, p2, p4});
    g2->setLeader(p3);
    g2->setPersons({p3});
    QSharedPointer<WorkerGroup> wg = QSharedPointer<WorkerGroup>(new
                                     WorkerGroup("Taskforce P&H", 50));
    wg->addWorker(p2);
    wg->addWorker(p3);
    auto gEnt = g.objectCast<Entity>();
    auto g2Ent = g2.objectCast<Entity>();
    auto wgEnt = wg.objectCast<Entity>();
    try {
        QVERIFY(this->e->save(gEnt));
        QVERIFY(this->e->save(wgEnt));
        QVERIFY(this->e->save(g2Ent));
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

void QuerybuilderTest::testFindByAttributesManyToOneRelation() {
    QHash<QString, QVariant> attributes;
    attributes["firstName"] = QString("Lucien");
    attributes["familyName"] = QString("We");
    QSharedPointer<Person> p = e->findEntityByAttributes<Person>(attributes, true);
    QVERIFY(p);
    attributes.clear();
    attributes["leader"] = QVariant(p);
    QSharedPointer<Group> group = e->findEntityByAttributes<Group>
                                  (attributes, true);
    QVERIFY(group);
    QCOMPARE(group->getName(), QString("Group Psy"));
}

void QuerybuilderTest::testFindByAttributesManyToOneRelationAttribute() {
    QHash<QString, QVariant> attributes;
    attributes["leader.firstName"] = QString("Fenja");
    QSharedPointer<Group> group = e->findEntityByAttributes<Group>
                                  (attributes, true);
    QVERIFY(group);
}

void QuerybuilderTest::testFindByAttributesManyToManyRelation() {
    QHash<QString, QVariant> attributes;
    attributes["persNumber"] = 42;
    QSharedPointer<Person> p = e->findEntityByAttributes<Person>(attributes, true);
    QVERIFY(p);
    QCOMPARE(p->getNickName(), QString("Lotta"));
    attributes.clear();
    attributes["persons"] = QVariant(p);
    QSharedPointer<Group> group = e->findEntityByAttributes<Group>
                                  (attributes, true);
    QVERIFY(group);
    QCOMPARE(group->getName(), QString("Group Health"));
}

void QuerybuilderTest::testFindByAttributesManyToManyRelationWithList() {
    QHash<QString, QVariant> attributes;
    QList<QSharedPointer<Person>> persons = QList<QSharedPointer<Person>>();
    attributes["firstName"] = QString("Lucien");
    QSharedPointer<Person> p1 = e->findEntityByAttributes<Person>(attributes, true);
    QVERIFY(p1);
    QCOMPARE(p1->getFamilyName(), QString("We"));
    persons.append(p1);
    attributes["firstName"] = QString("Janine");
    QSharedPointer<Person> p2 = e->findEntityByAttributes<Person>(attributes, true);
    QVERIFY(p2);
    QCOMPARE(p2->getFamilyName(), QString("Musterfrau"));
    persons.append(p2);
    attributes.clear();
    QVariant var;
    var.setValue<QList<QSharedPointer<Person>>>(persons);
    attributes["persons"] = var;
    QSharedPointer<Group> group = e->findEntityByAttributes<Group>
                                  (attributes, true);
    QVERIFY(group);
    QCOMPARE(group->getName(), QString("Group Psy"));
}

void QuerybuilderTest::testFindByAttributesManyToManyRelationAttribute() {
    QHash<QString, QVariant> attributes;
    attributes["persons.firstName"] = QString("Janine");
    QSharedPointer<Group> group = e->findEntityByAttributes<Group>
                                  (attributes, true);
    QVERIFY(group);
    QCOMPARE(group->getName(), QString("Group Psy"));
}

void QuerybuilderTest::testQueryBuilder() {
//    Query q = Query();
//    q.appendWhere(e->getQueryBuilder()->like(QString("firstname"), QString("Tim"),
//                  JokerPosition::BEHIND));
//    q.appendWhere(e->getQueryBuilder()->andOperator());
//    q.appendWhere(e->getQueryBuilder()->arbitraryOperator("<", "birthday",
//                  QDate(2000, 10, 10)));
//    //q.appendJoin(Join("person", "pupil.id = person.id"));
//    q.setDistinct(true);
//    q.appendOrderBy(OrderBy(QString("birthday"), Direction::SORT_DESC));
//    q.setLimit(10);
    //    QList<QSharedPointer<Pupil>> list = e->find<Pupil>(q, true);
}
