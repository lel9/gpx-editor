#include <QString>
#include <QtTest>

#include "../../src/converter.h"
#include "../../src/exceptions.h"

Q_DECLARE_METATYPE(shared_ptr<Route>)

class RouteToPolylineTest : public QObject
{
    Q_OBJECT

public:
    RouteToPolylineTest();

private Q_SLOTS:
    // ok
    void testCase1_data();
    void testCase1();

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

RouteToPolylineTest::RouteToPolylineTest()
{
}

void RouteToPolylineTest::testCase1_data()
{
    QTest::addColumn<shared_ptr<Route>>("route");
    QTest::addColumn<QString>("polyline");

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
}

void RouteToPolylineTest::testCase1()
{
    QFETCH(shared_ptr<Route>, route);
    QFETCH(QString, polyline);
    QCOMPARE(Converter::routeToPolyline(route), polyline);
}

void RouteToPolylineTest::test1()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    QTest::newRow("1") << mroute << "";
}

void RouteToPolylineTest::test2()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(0, 0));
    QTest::newRow("2") << mroute << "??";
}

void RouteToPolylineTest::test3()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(1, 1));
    mroute->appendPoint(QGeoCoordinate(2, 2));
    mroute->appendPoint(QGeoCoordinate(3, 3));

    QTest::newRow("3") << mroute << "_ibE_ibE_ibE_ibE_ibE_ibE";
}

void RouteToPolylineTest::test4()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(-1, -1));
    mroute->appendPoint(QGeoCoordinate(-2, -2));
    mroute->appendPoint(QGeoCoordinate(-3, -3));

    QTest::newRow("4") << mroute << "~hbE~hbE~hbE~hbE~hbE~hbE";
}

void RouteToPolylineTest::test5()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(1, 2));
    mroute->appendPoint(QGeoCoordinate(3, 4));
    mroute->appendPoint(QGeoCoordinate(5, 6));

    QTest::newRow("5") << mroute << "_ibE_seK_seK_seK_seK_seK";
}

void RouteToPolylineTest::test6()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(-1, 2));
    mroute->appendPoint(QGeoCoordinate(3, -3));
    mroute->appendPoint(QGeoCoordinate(4, 5));

    QTest::newRow("6") << mroute << "~hbE_seK_glW~po]_ibE_oyo@";
}

void RouteToPolylineTest::test7()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(1.5, 2.6789));
    mroute->appendPoint(QGeoCoordinate(-3.12345, 2.123456));
    mroute->appendPoint(QGeoCoordinate(3.123, -4.1));

    QTest::newRow("7") << mroute << "_~cHcfjOp_f[nnkBi_ce@ro~d@";
}

void RouteToPolylineTest::test8()
{
    shared_ptr<Route> mroute = make_shared<Route>();
    mroute->appendPoint(QGeoCoordinate(90, -180));
    mroute->appendPoint(QGeoCoordinate(-90, 180));

    QTest::newRow("8") << mroute << "_cidP~fsia@~fsia@_ogtcA";
}

QTEST_MAIN(RouteToPolylineTest)

#include "tst_route_to_polyline_test.moc"
