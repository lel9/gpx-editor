#include <QString>
#include <QtTest>

#include "../../src/converter.h"
#include "../../src/exceptions.h"

Q_DECLARE_METATYPE(shared_ptr<Route>)

class PolylineToRouteTest : public QObject
{
    Q_OBJECT

public:
    PolylineToRouteTest();

private Q_SLOTS:
    //ok
    void testCase1_data();
    void testCase1();
    // exceptions
    void testCase2_data();
    void testCase2();

private:
    void test1();
    void test2();
    void test3();
    void test4();
    void test5();
    void test6();
    void test7();
    void test8();
    void test9();
};

PolylineToRouteTest::PolylineToRouteTest()
{
}

void PolylineToRouteTest::testCase1_data()
{
    QTest::addColumn<QString>("polyline");
    QTest::addColumn<shared_ptr<Route>>("route");

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
}

void PolylineToRouteTest::testCase1()
{
    QFETCH(QString, polyline);
    QFETCH(shared_ptr<Route>, route);
    QCOMPARE(*(Converter::polylineToRoute(polyline)), *route);
}

void PolylineToRouteTest::testCase2_data()
{
    QTest::addColumn<QString>("polyline");
    QTest::newRow("10") << "12345";
}

void PolylineToRouteTest::testCase2()
{
    QFETCH(QString, polyline);
    QVERIFY_EXCEPTION_THROWN(Converter::polylineToRoute(polyline), DecoderException);
}

void PolylineToRouteTest::test1()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    QTest::newRow("1") << "" << mroute;
}

void PolylineToRouteTest::test2()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(0, 0));
    QTest::newRow("2") << "??" << mroute;
}

void PolylineToRouteTest::test3()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(1, 1));
    mroute->appendPoint(QGeoCoordinate(2, 2));
    mroute->appendPoint(QGeoCoordinate(3, 3));

    QTest::newRow("3") << "_ibE_ibE_ibE_ibE_ibE_ibE" << mroute;
}

void PolylineToRouteTest::test4()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(-1, -1));
    mroute->appendPoint(QGeoCoordinate(-2, -2));
    mroute->appendPoint(QGeoCoordinate(-3, -3));

    QTest::newRow("4") << "~hbE~hbE~hbE~hbE~hbE~hbE" << mroute;
}

void PolylineToRouteTest::test5()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(1, 2));
    mroute->appendPoint(QGeoCoordinate(3, 4));
    mroute->appendPoint(QGeoCoordinate(5, 6));

    QTest::newRow("5") << "_ibE_seK_seK_seK_seK_seK" << mroute;
}

void PolylineToRouteTest::test6()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(-1, 2));
    mroute->appendPoint(QGeoCoordinate(3, -3));
    mroute->appendPoint(QGeoCoordinate(4, 5));

    QTest::newRow("6") << "~hbE_seK_glW~po]_ibE_oyo@" << mroute;
}

void PolylineToRouteTest::test7()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(1.5, 2.6789));
    mroute->appendPoint(QGeoCoordinate(-3.12345, 2.12346));
    mroute->appendPoint(QGeoCoordinate(3.123, -4.1));

    QTest::newRow("7") << "_~cHcfjOp_f[nnkBi_ce@ro~d@" << mroute;
}

void PolylineToRouteTest::test8()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(90, -180));
    mroute->appendPoint(QGeoCoordinate(-90, 180));

    QTest::newRow("8") << "_cidP~fsia@~fsia@_ogtcA" << mroute;
}

void PolylineToRouteTest::test9()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(-0.00007, 0.00006));
    mroute->appendPoint(QGeoCoordinate(-0.00013, 0.00011));
    mroute->appendPoint(QGeoCoordinate(-0.00018, 0.00015));

    QTest::newRow("9") << "LKJIHG" << mroute;
}

QTEST_APPLESS_MAIN(PolylineToRouteTest)

#include "tst_polyline_to_route_test.moc"
