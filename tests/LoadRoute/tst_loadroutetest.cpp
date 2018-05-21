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

class LoadRouteTest : public QObject
{
    Q_OBJECT
public:
    LoadRouteTest();

private Q_SLOTS:
    //ok
    void testCase1_data();
    void testCase1();

private:
    void test1();
};

LoadRouteTest::LoadRouteTest()
{
}

void LoadRouteTest::testCase1_data()
{
    QTest::addColumn<Presenter*>("presenter");
    QTest::addColumn<RouteTableModel*>("model");
    QTest::addColumn<TestView*>("view");
    QTest::addColumn<RouteTableModel*>("resModel");
    QTest::addColumn<TestView*>("resView");

    test1();
}

void LoadRouteTest::testCase1()
{
    QFETCH(Presenter*, presenter);
    QFETCH(RouteTableModel*, model);
    QFETCH(TestView*, view);
    QFETCH(RouteTableModel*, resModel);
    QFETCH(TestView*, resView);

    model->setFileNameToSave("src/test_routes1.xml");
    presenter->recoverRoutes();

    QCOMPARE(*model, *resModel);
    QCOMPARE(*view, *resView);
}

void LoadRouteTest::test1()
{
    RouteTableModel *model = new RouteTableModel;
    RouteTableModel *resModel = new RouteTableModel;
    QVector<RouteData> routeData, resRouteData;

    RouteData data {"route1", 0, QDate(2018, 5, 21)};
    resRouteData << data;

    shared_ptr<Route> route = RouteFactory::create(data);
    route->appendPoint(QGeoCoordinate(1, 1));
    route->appendPoint(QGeoCoordinate(2, 2));
    route->appendPoint(QGeoCoordinate(3, 3));
    route->setPolyline("_ibE_ibE_ibE_ibE_ibE_ibE");
    resModel->addRoute(route);

    QVector<PointData> resPointData;
    PointData pointData1 {1, 1, 0};
    PointData pointData2 {2, 2, 0};
    PointData pointData3 {3, 3, 0};
    resPointData << pointData1 << pointData2 << pointData3;

    TestView *view = new TestView(routeData, QVector<PointData>());
    TestView *resView = new TestView(resRouteData, resPointData);

    resView->selectRoute(0);
    resView->setPolyline("_ibE_ibE_ibE_ibE_ibE_ibE");

    Presenter *presenter = new Presenter(view, model);

    QTest::newRow("0") << presenter << model << view << resModel << resView;
}

QTEST_APPLESS_MAIN(LoadRouteTest)

#include "tst_loadroutetest.moc"
