#ifndef BASEVIEW_H
#define BASEVIEW_H

#include "enum_insert_point.h"
#include "table_index.h"

#include <QString>
#include <QVariant>

class Presenter;


class BaseView
{
protected:
    Presenter *presenter;
public:
    BaseView() { }
    virtual ~BaseView() { }

    virtual int selectedRouteRow() const = 0;
    virtual int selectedPointRow() const = 0;

    virtual QString polyline() const = 0;
    virtual QVariant routeData(const TableIndex &index) const = 0;
    virtual QVariant pointData(const TableIndex &index) const = 0;
    virtual int routeViewRow() const = 0;
    virtual int pointViewRow() const = 0;
    virtual int routeViewColumn() const = 0;
    virtual int pointViewColumn() const = 0;
    virtual QVector<double> plotKeys() const = 0;
    virtual QVector<double> plotValues() const = 0;

    virtual BaseView* copy() = 0;

    virtual void currentRouteChanged() = 0;

    virtual void setPolyline(const QString &polyline) = 0;
    virtual void setRouteViewSize(int rowCount, int columnCount) = 0;
    virtual void setPointViewSize(int rowCount, int columnCount) = 0;
    virtual void setRouteViewHeaders(const QStringList &header) = 0;
    virtual void setPointViewHeaders(const QStringList &header) = 0;
    virtual void updateRouteView(const TableIndex &index, const QVariant &data) = 0;
    virtual void updatePointView(const TableIndex &index, const QVariant &data) = 0;
    virtual void setPlotData(const QVector<double> &keys, const QVector<double> &values) = 0;

    virtual void showErrorMessage(const QString &message) = 0;

    virtual void setOperationResult(const QString &result) = 0;

public slots:
    virtual void setUndoEnabled(bool enable) = 0;
    virtual void setRedoEnabled(bool enable) = 0;

    virtual void selectRoute(int row) = 0;

    virtual void addOperation(const QString &name) = 0;
    virtual void removeOperation(int index) = 0;
};

#endif // BASEVIEW_H
