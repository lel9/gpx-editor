#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QDate>
#include <QVector>

#include "../src/baseview.h"
#include "../tests/data_struct.h"

class TestView :  public QObject, public BaseView
{
    Q_OBJECT

private:
    QVector<RouteData> _routeData;
    QVector<PointData> _pointData;

    int _selectedRouteRow;
    int _selectedPointRow;

    QVector<double> _plotKeys;
    QVector<double> _plotValues;

    QString _polyline;

public:
    TestView() { }
    TestView(const QVector<RouteData> routes, QVector<PointData> points);
    TestView(const TestView &other);
    ~TestView();

    virtual int selectedRouteRow() const override;
    virtual int selectedPointRow() const override;

    virtual QString polyline() const override;
    virtual QVariant routeData(const TableIndex &index) const override;
    virtual QVariant pointData(const TableIndex &index) const override;
    virtual int routeViewRow() const override;
    virtual int pointViewRow() const override;
    virtual int routeViewColumn() const override;
    virtual int pointViewColumn() const override;
    virtual QVector<double> plotKeys() const override;
    virtual QVector<double> plotValues() const override;

    virtual BaseView* copy() override;

    virtual void setPolyline(const QString &polyline) override;

    virtual void setRouteViewSize(int rowCount, int columnCount) override;
    virtual void setPointViewSize(int rowCount, int columnCount) override;
    virtual void setRouteViewHeaders(const QStringList &) override;
    virtual void setPointViewHeaders(const QStringList &) override;

    virtual void updateRouteView(const TableIndex &index, const QVariant &data) override;
    virtual void updatePointView(const TableIndex &index, const QVariant &data) override;
    virtual void setPlotData(const QVector<double> &keys, const QVector<double> &values) override;

    virtual void showErrorMessage(const QString &) override;
    virtual void setOperationResult(const QString &) override;

    friend bool operator ==(const TestView &first, const TestView &second);
    friend bool operator !=(const TestView &first, const TestView &second);

public slots:
    virtual void selectRoute(int row) override;
    virtual void selectPoint(int row) override;
    virtual void setUndoEnabled(bool) override;
    virtual void setRedoEnabled(bool) override;
    virtual void addOperation(const QString &) override;
    virtual void removeOperation(int) override;

signals:
    void currentRouteChanged();
};

#endif // TESTVIEW_H
