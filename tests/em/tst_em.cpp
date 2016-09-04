#include "tst_em.h"

void EmTest::initTestCase() {
    CuteEntityManager::EntityInstanceFactory::registerClass<Group>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Person>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Article>();
    CuteEntityManager::EntityInstanceFactory::registerClass<Employee>();
    CuteEntityManager::EntityInstanceFactory::registerClass<WorkerGroup>();
    this->e = new CuteEntityManager::EntityManager("QSQLITE",
            ":memory:", "", "", "", "", true, "foreign_keys = ON", false);
}

void EmTest::cleanupTestCase() {
    if (this->e) {
        delete this->e;
        this->e = nullptr;
    }
}

void EmTest::testCheckDuplicates() {
    QSharedPointer<Article> article = QSharedPointer<Article>(new Article(10,
                                      QString("TestItem")));
    QVERIFY(this->e->create(article));
    QSharedPointer<Entity> copy = QSharedPointer<Entity>(article->copy());
    QVERIFY(!this->e->create(copy, true, true));
}

void EmTest::testBasics() {
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
    QSharedPointer<Article> article2 = this->e->findEntityByAttributes<Article>(attrs);
    QVERIFY(article2);
    QVERIFY(this->e->remove(article2));
    QCOMPARE(this->e->count("article"), (quint32)0);
}

void EmTest::init() {
    QStringList inits = QStringList() << "Person" << "Group" << "Article";
    QVERIFY2(this->e->startup("emTestA", inits), "Failure");
    auto migrations = this->e->findAll<CuteEntityManager::DatabaseMigration>();
    QCOMPARE(migrations.size(), 1);
    QCOMPARE(migrations.at(0)->getVersion(), QString("emTestA"));
}

void EmTest::testDatabaseMigrationTable() {
    auto tables = this->e->getSchema()->getTables();
    QString tblName = "cuteentitymanager::databasemigration";
    bool containsMigration = tables.contains(tblName);
    QVERIFY(containsMigration);
    if(containsMigration) {
        auto schema = tables.value(tblName);
        auto columns = schema->getColumns();
        QCOMPARE(columns.size(), 3);
        this->containsColumn(columns, "id", QVariant::Int, tblName, true);
        this->containsColumn(columns, "version", QVariant::String);
        this->containsColumn(columns, "applyTime", QVariant::String);
    }
}

void EmTest::testTableCreation() {
    auto tables = this->e->getSchema()->getTables();
    bool containsArticle = tables.contains("article");
    QVERIFY(containsArticle);
    if(containsArticle) {
        auto schema = tables.value("article");
        auto columns = schema->getColumns();
        QCOMPARE(columns.size(), 3);
        this->containsColumn(columns, "id", QVariant::Int, "article", true);
        this->containsColumn(columns, "name", QVariant::String);
        this->containsColumn(columns, "price", QVariant::Double);
    }
    bool containsPerson = tables.contains("person");
    QVERIFY(containsPerson);
    if(containsPerson) {
        auto schema = tables.value("person");
        auto columns = schema->getColumns();
        QCOMPARE(columns.size(), 6);
        this->containsColumn(columns, "id", QVariant::Int, "person", true);
        this->containsColumn(columns, "firstName", QVariant::String);
        this->containsColumn(columns, "familyName", QVariant::String);
        this->containsColumn(columns, "birthday", QVariant::String);
        this->containsColumn(columns, "nickName", QVariant::String);
        this->containsColumn(columns, "gender", QVariant::Int);
    }
    bool containsGroup = tables.contains("group");
    QVERIFY(containsGroup);
    if(containsGroup) {
        auto schema = tables.value("group");
        auto columns = schema->getColumns();
        QCOMPARE(columns.size(), 3);
        this->containsColumn(columns, "id", QVariant::Int, "group", true);
        this->containsColumn(columns, "name", QVariant::String);
        this->containsColumn(columns, "leader_id", QVariant::Int);
    }
    bool containsPersonGroups = tables.contains("person_groups");
    QVERIFY(containsPersonGroups);
    if(containsArticle) {
        auto schema = tables.value("person_groups");
        auto columns = schema->getColumns();
        QCOMPARE(columns.size(), 3);
        this->containsColumn(columns, "id", QVariant::Int, "person_groups", true);
        this->containsColumn(columns, "person_id", QVariant::Int);
        this->containsColumn(columns, "group_id", QVariant::Int);
    }
    QVERIFY(!tables.contains("group_persons"));
}


void EmTest::containsColumn(QHash<QString, QSharedPointer<QSqlField>> &columns,
                            QString name,
                            QVariant::Type type, QString tableName, bool pk) {
    bool containsColumn = columns.contains(name);
    QVERIFY(containsColumn);
    if(containsColumn) {
        auto column = columns.value(name);
        qDebug() << name << column->type() << type;
        if(type != QVariant::UserType) {
            QCOMPARE(column->type(), type);
        }
        if(!name.isEmpty()) {
            QString pkIndex = this->e->getDb()->getDatabase().primaryIndex(tableName).fieldName(0);
            bool same = (pkIndex == name);
            QVERIFY((pk && same) || (!pk && !same));
        }
    }
}

void EmTest::cleanup() {
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

void EmTest::testRelationTableCreation() {
    this->createRelationTables();
    auto tables = this->e->getSchema()->getTables();
    QVERIFY(tables.contains("workergroup"));
    bool containsEmployee = tables.contains("employee");
    QVERIFY(containsEmployee);
    if(containsEmployee) {
        auto schema = tables.value("employee");
        auto columns = schema->getColumns();
        QCOMPARE(columns.size(), 4);
        this->containsColumn(columns, "id", QVariant::Int, "employee", false);
        this->containsColumn(columns, "persNumber", QVariant::String);
        this->containsColumn(columns, "manager", QVariant::Int);
        this->containsColumn(columns, "department", QVariant::String);
    }
    QVERIFY(tables.contains("workergroup_workers"));
    QVERIFY(!tables.contains("group_employee"));
    QVERIFY(!tables.contains("employee_workergroups"));
    QVERIFY(!tables.contains("employee_groups"));
    QVERIFY(tables.contains("cuteentitymanager::databasemigration"));
    auto migrations = this->e->findAll<CuteEntityManager::DatabaseMigration>();
    QCOMPARE(migrations.size(), 2);
    QCOMPARE(migrations.at(1)->getVersion(), QString("emTestB"));
    this->deleteRelationTables();
}

void EmTest::testInheritedRelations() {
    QSharedPointer<Employee> e1 = QSharedPointer<Employee>(new Employee(42, "Fenja", "S.",
                                  Person::Gender::FEMALE, "Lotta", QDate(1990, 10, 10), "Psychology"));
    QSharedPointer<Employee> e2 = QSharedPointer<Employee>(new Employee(11, "Janine",
                                  "Musterfrau",
                                  Person::Gender::FEMALE, "", QDate(2000, 1, 1), "Health", true));
    QSharedPointer<WorkerGroup> wg = QSharedPointer<WorkerGroup>(new
                                     WorkerGroup("Taskforce P&H", 42));
    wg->addWorker(e1);
    wg->addWorker(e2);
    try {
        QVERIFY(this->e->create(wg));
        QSharedPointer<Group> g = QSharedPointer<Group>(new Group("EmployeeGroup"));
        g->setPersons({e1, e2});
        QVERIFY(this->e->create(g));
        g->setName("Taskforce 0008");
        QVERIFY(this->e->merge(g));
        QVERIFY(this->e->remove(g));
    } catch(QString e) {
        QFAIL(e.toUtf8().constData());
    }
}

void EmTest::createRelationTables() {
    QStringList relationTables = QStringList() << "Employee" << "WorkerGroup";
    QVERIFY2(this->e->startup("emTestB", relationTables), "Failure");
}

void EmTest::deleteRelationTables() {
    auto qb = this->e->getQueryBuilder();
    QVERIFY(this->e->executeQuery(qb->dropTable("workergroup_workers")));
    QVERIFY(this->e->executeQuery(qb->dropTable("employee")));
    QVERIFY(this->e->executeQuery(qb->dropTable("workergroup")));
    auto tableNames = this->e->getSchema()->getTableNames();
    QVERIFY(!tableNames.contains("workergroup_workers"));
    QVERIFY(!tableNames.contains("employee"));
    QVERIFY(!tableNames.contains("workergroup"));
    QHash<QString, QVariant> attributes;
    attributes["version"] = QString("emTestB");
    QSharedPointer<DatabaseMigration> dbm = e->findEntityByAttributes<DatabaseMigration>
                                            (attributes, true);
    auto ent = dbm.objectCast<Entity>();
    QVERIFY(this->e->remove(ent));
    auto migrations = this->e->findAll<CuteEntityManager::DatabaseMigration>();
    QCOMPARE(migrations.size(), 1);
}

void EmTest::testFindById() {
    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Patrick", "De",
                               Person::Gender::MALE, "Pat", QDate(2000, 1, 1)));
    auto ent = p.objectCast<Entity>();
    QVERIFY(this->e->create(ent));
    auto id = p->getId();
    QVERIFY(id > -1);
    QVERIFY(this->e->findById(id, p->getClassname()));
}

void EmTest::testFindId() {
    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Essi", "Sa",
                               Person::Gender::MALE, "Essi", QDate(2000, 1, 1)));
    auto ent = p.objectCast<Entity>();
    QVERIFY(this->e->create(ent));
    auto entity = QSharedPointer<Entity>(p->copy());
    auto foundId = this->e->findId(entity);
    QVERIFY(foundId  > -1 && foundId == ent->getId());
}

void EmTest::testHasChanged() {
    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Jelena", "Fl",
                               Person::Gender::MALE, "Maxi", QDate(2000, 1, 1)));
    auto ent = p.objectCast<Entity>();
    QVERIFY(this->e->create(p));
    p->setFirstName("Laura");
    p->setFamilyName("Musterfrau");
    p->setBirthday(QDate(200, 1, 2));
    QVERIFY(this->e->hasChanged(ent));
}

void EmTest::testValidate() {
    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Patrick", "Pe",
                               Person::Gender::MALE, "Maxi", QDate(2000, 1, 1)));
    auto ent = p.objectCast<Entity>();
    QVERIFY(this->e->validate(ent));
    p->setFirstName("M");
    QVERIFY(!this->e->validate(ent) && ent->getErrors().size() == 1);
    p->setBirthday(QDate(2030, 10, 10));
    QVERIFY(!this->e->validate(ent) && ent->getErrors().size() == 2);
}

void EmTest::testRelations() {
    QSharedPointer<Person> p1 = QSharedPointer<Person>(new Person("Lucien", "We",
                                Person::Gender::MALE, "Luc", QDate(2000, 1, 1)));
    QSharedPointer<Person> p2 = QSharedPointer<Person>(new Person("Janine", "Musterfrau",
                                Person::Gender::FEMALE, "", QDate(2000, 1, 1)));
    QSharedPointer<Person> p3 = QSharedPointer<Person>(new Person("Fenja", "Sey.",
                                Person::Gender::FEMALE, "Lotta", QDate(1990, 11, 11)));
    QSharedPointer<Group> g = QSharedPointer<Group>(new Group("TestGroup"));
    QSharedPointer<Group> g2 = QSharedPointer<Group>(new Group("TestGroup2"));
    g->setLeader(p1);
    g2->setLeader(p2);
    g->setPersons({p1});
    auto pEnt = p3.objectCast<Entity>();
    auto pEnt1 = p1.objectCast<Entity>();
    QVERIFY(this->e->save(g));
    auto maintainedGroups = p1->getMaintainedGroups();
    maintainedGroups.append(g2);
    p1->setMaintainedGroups(maintainedGroups);
    this->e->merge(pEnt1, true, false, true);
    QVERIFY(p1->getId() > -1);
    QCOMPARE(p1->getMaintainedGroups().size(), 2);
    QVERIFY(p1->getGroups().size() > 0);
    g->addPerson(p2);
    g->setName("TestGroupExtended");
    QVERIFY(this->e->save(g));
    p3->setGroups({g});
    QVERIFY(this->e->save(pEnt, true, true));
    QVERIFY(g->getPersons().size() == 3);
    QList<QSharedPointer<Group>> groups;
    p3->setGroups(groups);
    QVERIFY(this->e->save(pEnt, true, true));
    this->e->refresh(g);
    QVERIFY(g->getPersons().size() == 3);
    auto firstPerson = g->getPersons().first();
    g->removePerson(firstPerson);
    QVERIFY(this->e->save(g, true, true));
    this->e->refresh(firstPerson);
    QVERIFY(firstPerson->getGroups().size() == 0);
    QVERIFY(g->getPersons().size() == 1);
}
