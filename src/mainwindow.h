#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

#include <memory>
using namespace std;

#include "table_point_item_delegate.h"
#include "baseview.h"
#include "presenter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public BaseView
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    TablePointItemDelegate *delegate;

private slots:
    void on_pointChanged(QTableWidgetItem* item);
    void on_routeChanged(QTableWidgetItem* item);

    void on_actionImportGPX_triggered();
    void on_actionImportPolyline_triggered();

    void on_actionAddRoute_triggered();
    void on_actionDeleteRoute_triggered();

    void on_Undo_triggered();
    void on_Redo_triggered();

    void on_actionInsertPointBefore_triggered();
    void on_actionDeletePoint_triggered();
    void on_actionInsertPointAfter_triggered();

    void on_pushButton_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    virtual void setRouteViewHeaders(const QStringList &header) override;
    virtual void setPointViewHeaders(const QStringList &header) override;

    virtual void updateRouteView(const TableIndex &index, const QVariant &data) override;
    virtual void updatePointView(const TableIndex &index, const QVariant &data) override;
    virtual void setPlotData(const QVector<double> &keys, const QVector<double> &values) override;

    virtual void showErrorMessage(const QString &message) override;
    virtual void setOperationResult(const QString &result) override;

    virtual void closeEvent(QCloseEvent *);

signals:
    void currentRouteChanged();

public slots:
    virtual void setUndoEnabled(bool enable) override;
    virtual void setRedoEnabled(bool enable) override;

    virtual void selectRoute(int row) override;

    virtual void addOperation(const QString &name) override;
    virtual void removeOperation(int index) override;
};

#endif // MAINWINDOW_H
