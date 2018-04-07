#include <QString>
#include <QtTest>

#include "../../src/route_table_model.h"
#include "../../src/exceptions.h"
#include "../../src/presenter.h"
#include "../testview.h"
#include "random_route_factory.h"

Q_DECLARE_METATYPE(shared_ptr<Route>)
Q_DECLARE_METATYPE(RouteTableModel)
Q_DECLARE_METATYPE(Presenter)
Q_DECLARE_METATYPE(TestView)

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
    QTest::addColumn<Presenter>("presenter");
    QTest::addColumn<RouteTableModel>("model");
    QTest::addColumn<TestView>("view");
    QTest::addColumn<int>("index");
    QTest::addColumn<RouteTableModel>("resModel");
    QTest::addColumn<TestView>("resView");

    for (int i = 0; i < ROUTES_COUNT; i++)
        test1(i);
}

void RemoveRouteTest::testCase1()
{
    QFETCH(Presenter, presenter);
    QFETCH(RouteTableModel, model);
    QFETCH(TestView, view);
    QFETCH(int, index);
    QFETCH(RouteTableModel, resModel);
    QFETCH(TestView, resView);

    view.selectRoute(index);
    view.deleteRoute();

    QCOMPARE(model, resModel);
    QCOMPARE(view, resView);
}

void RemoveRouteTest::testCase2_data()
{
//    QTest::addColumn<RouteTableModel>("data");
//    QTest::addColumn<int>("index");

//    test2(-1);
//    test2(ROUTES_COUNT);
}

void RemoveRouteTest::testCase2()
{
//    QFETCH(RouteTableModel, data);
//    QFETCH(int, index);
//    QVERIFY_EXCEPTION_THROWN(data.removeRoute(index), std::out_of_range);
}

void RemoveRouteTest::test1(int index)
{
    RouteTableModel model, resModel;
    char **r = nullptr;
    int j = 0;
    QApplication app(j, r);
    TestView view, resView;
    Presenter presenter(&view, &model);

    for (int i = 0; i < ROUTES_COUNT; i++)
    {
        shared_ptr<Route> route = RandomRouteFactory::create(POINTS_COUNT);
        model.addRoute(route);
        if (i != index)
            resModel.addRoute(route);
    }

    view.setRouteView(&model);
    resView.setRouteView(&resModel);

    if (index == ROUTES_COUNT-1)
        resModel.setCurrentRoute(index-1);
    else
        resModel.setCurrentRoute(index);

    resView.selectRoute(resModel.currentRoute());
    resView.setPointView(resModel.currentPointModel());
    resView.setPolyline(resModel.currentPolyline());

    char *testNumber = QString::number(index).toUtf8().data();
    QTest::newRow(testNumber) << presenter << model << view << index << resModel << resView;
}

void RemoveRouteTest::test2(int index)
{
//    RouteTableModel mdata;
//    for (int i = 0; i < ROUTES_COUNT; i++)
//        mdata.addRoute(RandomRouteFactory::create(POINTS_COUNT));

//    QTest::newRow(QString::number(index).toUtf8().data()) << mdata << index;
}

QTEST_APPLESS_MAIN(RemoveRouteTest)

#include "tst_remove_route_test.moc"
