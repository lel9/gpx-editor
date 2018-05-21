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

class AddRouteTest : public QObject
{
    Q_OBJECT
public:
    AddRouteTest();

private Q_SLOTS:
    //ok
    void testCase1_data();
    void testCase1();

private:
    void test1();
};

AddRouteTest::AddRouteTest()
{
}

void AddRouteTest::testCase1_data()
{
    QTest::addColumn<Presenter*>("presenter");
    QTest::addColumn<RouteTableModel*>("model");
    QTest::addColumn<TestView*>("view");
    QTest::addColumn<RouteTableModel*>("resModel");
    QTest::addColumn<TestView*>("resView");

    test1();
}

void AddRouteTest::testCase1()
{
    QFETCH(Presenter*, presenter);
    QFETCH(RouteTableModel*, model);
    QFETCH(TestView*, view);
    QFETCH(RouteTableModel*, resModel);
    QFETCH(TestView*, resView);

    presenter->on_addRoute();

    QCOMPARE(*model, *resModel);
    QCOMPARE(*view, *resView);
}

void AddRouteTest::test1()
{
    RouteTableModel *model = new RouteTableModel;
    RouteTableModel *resModel = new RouteTableModel;
    QVector<RouteData> routeData, resRouteData;

    RouteData data {"Новый маршрут", 0, QDate::currentDate()};
    resRouteData << data;

    shared_ptr<Route> route = RouteFactory::create(data);
    resModel->addRoute(route);

    TestView *view = new TestView(routeData, QVector<PointData>());
    TestView *resView = new TestView(resRouteData, QVector<PointData>());

    resView->selectRoute(0);

    Presenter *presenter = new Presenter(view, model);

    QTest::newRow("0") << presenter << model << view << resModel << resView;
}

QTEST_APPLESS_MAIN(AddRouteTest)

#include "tst_addroutetest.moc"
