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

class EditPointTest : public QObject
{
    Q_OBJECT
public:
    EditPointTest();

private Q_SLOTS:
    //ok
    void testCase1_data();
    void testCase1();

private:
    void test1();
};

EditPointTest::EditPointTest()
{
}

void EditPointTest::testCase1_data()
{
    QTest::addColumn<Presenter*>("presenter");
    QTest::addColumn<RouteTableModel*>("model");
    QTest::addColumn<TestView*>("view");
    QTest::addColumn<RouteTableModel*>("resModel");
    QTest::addColumn<TestView*>("resView");

    test1();
}

void EditPointTest::testCase1()
{
    QFETCH(Presenter*, presenter);
    QFETCH(RouteTableModel*, model);
    QFETCH(TestView*, view);
    QFETCH(RouteTableModel*, resModel);
    QFETCH(TestView*, resView);

    presenter->on_pointChanged(TableIndex(0,0), 0);

    QCOMPARE(*model, *resModel);
    QCOMPARE(*view, *resView);
}

void EditPointTest::test1()
{
    RouteTableModel *model = new RouteTableModel;
    RouteTableModel *resModel = new RouteTableModel;
    QVector<RouteData> routeData, resRouteData;

    RouteData data {"Новый маршрут", 0, QDate::currentDate()};
    resRouteData << data;
    routeData << data;

    shared_ptr<Route> route = RouteFactory::create(data);
    route->appendPoint(QGeoCoordinate(1, 0, 0));
    model->addRoute(route);

    shared_ptr<Route> routeRes = RouteFactory::create(data);
    routeRes->appendPoint(QGeoCoordinate(0, 0, 0));
    resModel->addRoute(routeRes);

    PointData pointData { 1, 0, 0 };
    QVector<PointData> points;
    points << pointData;

    PointData pointDataRes { 0, 0, 0 };
    QVector<PointData> pointsRes;
    pointsRes << pointDataRes;

    TestView *view = new TestView(routeData, points);
    TestView *resView = new TestView(resRouteData, pointsRes);

    resView->selectRoute(0);
    resView->setPolyline("??");
    QVector<double> keys;
    keys << 0;
    resView->setPlotData(keys, keys);

    Presenter *presenter = new Presenter(view, model);

    QTest::newRow("0") << presenter << model << view << resModel << resView;
}

QTEST_APPLESS_MAIN(EditPointTest)

#include "tst_editpointtest.moc"
