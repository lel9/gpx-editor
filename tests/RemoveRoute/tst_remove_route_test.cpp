#include <QString>
#include <QtTest>

#include "../../src/route_table_model.h"
#include "../../src/exceptions.h"
#include "../../src/presenter.h"
#include "../testview.h"
#include "route_factory.h"

Q_DECLARE_METATYPE(shared_ptr<Route>)
Q_DECLARE_METATYPE(RouteTableModel)
Q_DECLARE_METATYPE(Presenter)
Q_DECLARE_METATYPE(TestView)

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
    void test1(int index, int routeCount);
    void test2(int index, int routeCount);
};

RemoveRouteTest::RemoveRouteTest()
{
}

void RemoveRouteTest::testCase1_data()
{
    QTest::addColumn<Presenter*>("presenter");
    QTest::addColumn<RouteTableModel*>("model");
    QTest::addColumn<TestView*>("view");
    QTest::addColumn<int>("index");
    QTest::addColumn<RouteTableModel*>("resModel");
    QTest::addColumn<TestView*>("resView");

    test1(0, 5);
    test1(0, 1);
    test1(3, 5);
    test1(4, 5);
}

void RemoveRouteTest::testCase1()
{
    QFETCH(Presenter*, presenter);
    QFETCH(RouteTableModel*, model);
    QFETCH(TestView*, view);
    QFETCH(int, index);
    QFETCH(RouteTableModel*, resModel);
    QFETCH(TestView*, resView);

    view->selectRoute(index);
    presenter->on_deleteRoute();

    QCOMPARE(*model, *resModel);
    QCOMPARE(*view, *resView);
}

void RemoveRouteTest::testCase2_data()
{
    QTest::addColumn<Presenter*>("presenter");
    QTest::addColumn<RouteTableModel*>("model");
    QTest::addColumn<TestView*>("view");
    QTest::addColumn<int>("index");

    test2(-1, 5);
    test2(5, 5);
}

void RemoveRouteTest::testCase2()
{
    QFETCH(Presenter*, presenter);
    QFETCH(RouteTableModel*, model);
    QFETCH(TestView*, view);
    QFETCH(int, index);

    view->selectRoute(index);
    presenter->on_deleteRoute();

    QVERIFY_EXCEPTION_THROWN(model->removeRoute(index), std::out_of_range);
}

void RemoveRouteTest::test1(int index, int routeCount)
{
    RouteTableModel *model = new RouteTableModel;
    RouteTableModel *resModel = new RouteTableModel;
    QVector<RouteData> routeData, resRouteData;

    for (int i = 0; i < routeCount; i++)
    {
        RouteData data {"route" + QString::number(i+1), i*10., QDate(2018, 4, i+1)};
        routeData << data;

        shared_ptr<Route> route = RouteFactory::create(data);
        model->addRoute(route);
        if (i != index)
        {
            resModel->addRoute(route);
            resRouteData << data;
        }
    }

    TestView *view = new TestView(routeData, QVector<PointData>());
    TestView *resView = new TestView(resRouteData, QVector<PointData>());

    if (index < model->rowCount()-1)
        resView->selectRoute(index);
    else
        resView->selectRoute(index-1);

    Presenter *presenter = new Presenter(view, model);

    char *t = (QString::number(index) + ", " + QString::number(routeCount)).toUtf8().data();
    QTest::newRow(t) << presenter << model << view << index << resModel << resView;
}

void RemoveRouteTest::test2(int index, int routeCount)
{
    RouteTableModel *model = new RouteTableModel;
    QVector<RouteData> routeData;

    for (int i = 0; i < routeCount; i++)
    {
        RouteData data {"route" + QString::number(i+1), i*10., QDate(2018, 4, i+1)};
        routeData << data;

        shared_ptr<Route> route = RouteFactory::create(data);
        model->addRoute(route);
    }

    TestView *view = new TestView(routeData, QVector<PointData>());
    Presenter *presenter = new Presenter(view, model);

    char *t = (QString::number(index) + ", " + QString::number(routeCount)).toUtf8().data();
    QTest::newRow(t) << presenter << model << view << index;
}

QTEST_APPLESS_MAIN(RemoveRouteTest)

#include "tst_remove_route_test.moc"
