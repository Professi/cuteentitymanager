#include <QString>
#include <QtTest>

class QuerybuilderTest : public QObject
{
    Q_OBJECT

public:
    QuerybuilderTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();
};

QuerybuilderTest::QuerybuilderTest()
{
}

void QuerybuilderTest::initTestCase()
{
}

void QuerybuilderTest::cleanupTestCase()
{
}

void QuerybuilderTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void QuerybuilderTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(QuerybuilderTest)

#include "tst_querybuildertest.moc"
