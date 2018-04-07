#ifndef TESTVIEW_H
#define TESTVIEW_H

#include "../src/baseview.h"

class TestView : public BaseView
{
private:
    TableWidget *_routeView;
    TableWidget *_pointView;
    GraphPlot *_graphPlot;
    QTextEdit *_polylineEdit;

public:
    TestView(QWidget *parent = 0);
    TestView(const TestView &other);
    ~TestView();

    virtual TableWidget *routeView() const override;
    virtual TableWidget *pointView() const override;
    virtual GraphPlot *graphPlot() const override;
    virtual QTextEdit *polylineEdit() const override;

    virtual QModelIndexList selectedRouteRows() const override;
    virtual QModelIndexList selectedPointRows() const override;

    virtual void setUndoEnabled(bool) override;
    virtual void setRedoEnabled(bool) override;

    friend bool operator ==(const TestView &first, const TestView &second);
    friend bool operator !=(const TestView &first, const TestView &second);

public slots:
    virtual void setPolyline(const QString &polyline) override;
    virtual void updateRouteView(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                  RouteTableModel *model) override;
    virtual void updatePointView(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                  PointTableModel *model) override;

    virtual void showErrorMessage(const QString &) override;

    virtual void selectRoute(int row) override;

    void setRouteView(RouteTableModel *model);
    void setPointView(PointTableModel *model);
};

#endif // TESTVIEW_H
