#include <QString>
#include <QtTest>

#include "../../src/route_table_model.h"
#include "../../src/exceptions.h"
#include "../../src/presenter.h"
#include "../testview.h"
#include "../route_factory.h"

Q_DECLARE_METATYPE(shared_ptr<Route>)
Q_DECLARE_METATYPE(RouteTableModel)
Q_DECLARE_METATYPE(Presenter)
Q_DECLARE_METATYPE(TestView)

class AddPointTest : public QObject
{
    Q_OBJECT
public:
    AddPointTest();

private Q_SLOTS:
    //ok
    void testCase1_data();
    void testCase1();

private:
    void test1();
};

AddPointTest::AddPointTest()
{
}

void AddPointTest::testCase1_data()
{
    QTest::addColumn<Presenter*>("presenter");
    QTest::addColumn<RouteTableModel*>("model");
    QTest::addColumn<TestView*>("view");
    QTest::addColumn<RouteTableModel*>("resModel");
    QTest::addColumn<TestView*>("resView");

    test1();
}

void AddPointTest::testCase1()
{
    QFETCH(Presenter*, presenter);
    QFETCH(RouteTableModel*, model);
    QFETCH(TestView*, view);
    QFETCH(RouteTableModel*, resModel);
    QFETCH(TestView*, resView);

    presenter->on_insertPoint(InsertPointPos::After);

    QCOMPARE(*model, *resModel);
    QCOMPARE(*view, *resView);
}

void AddPointTest::test1()
{
    RouteTableModel *model = new RouteTableModel;
    RouteTableModel *resModel = new RouteTableModel;
    QVector<RouteData> routeData, resRouteData;

    RouteData data {"Новый маршрут", 0, QDate::currentDate()};
    resRouteData << data;
    routeData << data;

    shared_ptr<Route> route = RouteFactory::create(data);
    route->appendPoint(QGeoCoordinate(0, 0, 0));
    route->setPolyline("??");
    resModel->addRoute(route);

    model->addRoute(RouteFactory::create(data));

    PointData pointData { 0, 0, 0 };
    QVector<PointData> points;
    points << pointData;

    TestView *view = new TestView(routeData, QVector<PointData>());
    TestView *resView = new TestView(resRouteData, points);

    resView->selectRoute(0);
    resView->setPolyline("??");
    QVector<double> keys;
    keys << 0;
    resView->setPlotData(keys, keys);

    Presenter *presenter = new Presenter(view, model);

    QTest::newRow("0") << presenter << model << view << resModel << resView;
}

QTEST_APPLESS_MAIN(AddPointTest)

#include "tst_addpointtest.moc"
