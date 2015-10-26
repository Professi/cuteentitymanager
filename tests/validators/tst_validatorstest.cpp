#include <QString>
#include <QtTest>

class ValidatorsTest : public QObject
{
    Q_OBJECT

public:
    ValidatorsTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();
};

ValidatorsTest::ValidatorsTest()
{
}

void ValidatorsTest::initTestCase()
{
}

void ValidatorsTest::cleanupTestCase()
{
}

void ValidatorsTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void ValidatorsTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ValidatorsTest)

#include "tst_validatorstest.moc"
