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

class RemovePointTest : public QObject
{
    Q_OBJECT
public:
    RemovePointTest();

private Q_SLOTS:
    //ok
    void testCase1_data();
    void testCase1();

private:
    void test1();
};

RemovePointTest::RemovePointTest()
{
}

void RemovePointTest::testCase1_data()
{
    QTest::addColumn<Presenter*>("presenter");
    QTest::addColumn<RouteTableModel*>("model");
    QTest::addColumn<TestView*>("view");
    QTest::addColumn<RouteTableModel*>("resModel");
    QTest::addColumn<TestView*>("resView");

    test1();
}

void RemovePointTest::testCase1()
{
    QFETCH(Presenter*, presenter);
    QFETCH(RouteTableModel*, model);
    QFETCH(TestView*, view);
    QFETCH(RouteTableModel*, resModel);
    QFETCH(TestView*, resView);

    view->selectPoint(0);
    presenter->on_deletePoint();

    QCOMPARE(*model, *resModel);
    QCOMPARE(*view, *resView);
}

void RemovePointTest::test1()
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
    model->addRoute(route);

    resModel->addRoute(RouteFactory::create(data));

    TestView *view = new TestView(routeData, QVector<PointData>());
    TestView *resView = new TestView(resRouteData, QVector<PointData>());

    resView->selectRoute(0);

    Presenter *presenter = new Presenter(view, model);

    QTest::newRow("0") << presenter << model << view << resModel << resView;
}

QTEST_APPLESS_MAIN(RemovePointTest)

#include "tst_removepointtest.moc"
