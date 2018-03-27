#include <QString>
#include <QtTest>

#include "../../src/route_table_model.h"
#include "../../src/exceptions.h"
#include "random_route_factory.h"

Q_DECLARE_METATYPE(shared_ptr<Route>)
Q_DECLARE_METATYPE(RouteTableModel)


#define ROUTES_COUNT 5
#define POINTS_COUNT 5

class RemoveRouteTest : public QObject
{
    Q_OBJECT

public:
    RemoveRouteTest();

private Q_SLOTS:
    //ok
    void testCase1_data();
    void testCase1();
    //exceptions
    void testCase2_data();
    void testCase2();

private:
    void test1(int index);
    void test2(int index);
};

RemoveRouteTest::RemoveRouteTest()
{
}

void RemoveRouteTest::testCase1_data()
{
    QTest::addColumn<RouteTableModel>("data");
    QTest::addColumn<int>("index");
    QTest::addColumn<shared_ptr<Route>>("route");
    QTest::addColumn<RouteTableModel>("res");

    for (int i = 0; i < ROUTES_COUNT; i++)
        test1(i);
}

void RemoveRouteTest::testCase1()
{
    QFETCH(RouteTableModel, data);
    QFETCH(int, index);
    QFETCH(shared_ptr<Route>, route);
    QFETCH(RouteTableModel, res);
    shared_ptr<Route> remRoute = data.removeRoute(index);
    QCOMPARE(*remRoute, *route);
    QCOMPARE(data, res);
}

void RemoveRouteTest::testCase2_data()
{
    QTest::addColumn<RouteTableModel>("data");
    QTest::addColumn<int>("index");

    test2(-1);
    test2(ROUTES_COUNT);
}

void RemoveRouteTest::testCase2()
{
    QFETCH(RouteTableModel, data);
    QFETCH(int, index);
    QVERIFY_EXCEPTION_THROWN(data.removeRoute(index), std::out_of_range);
}

void RemoveRouteTest::test1(int index)
{
    RouteTableModel mdata, mres;
    shared_ptr<Route> remRoute;
    for (int i = 0; i < ROUTES_COUNT; i++)
    {
        shared_ptr<Route> route = RandomRouteFactory::create(POINTS_COUNT);
        mdata.addRoute(route);
        if (i != index)
            mres.addRoute(route);
        else
            remRoute = route;
    }

    QTest::newRow(QString::number(index).toUtf8().data()) << mdata << index << remRoute << mres;
}

void RemoveRouteTest::test2(int index)
{
    RouteTableModel mdata;
    for (int i = 0; i < ROUTES_COUNT; i++)
        mdata.addRoute(RandomRouteFactory::create(POINTS_COUNT));

    QTest::newRow(QString::number(index).toUtf8().data()) << mdata << index;
}

QTEST_APPLESS_MAIN(RemoveRouteTest)

#include "tst_remove_route_test.moc"
