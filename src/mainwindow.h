#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
using namespace std;

#include "table_point_item_delegate.h"
#include "baseview.h"
#include "presenter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public BaseView
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Presenter *presenter;
    TablePointItemDelegate *delegate;

private slots:
    void on_pointChanged(QTableWidgetItem* item);

    void on_actionImportGPX_triggered();
    void on_actionImportPolyline_triggered();

    void on_actionAddRoute_triggered();
    void on_actionDeleteRoute_triggered();

    void on_Undo_triggered();
    void on_Redo_triggered();

    void on_actionInsertPointBefore_triggered();
    void on_actionDeletePoint_triggered();
    void on_actionInsertPointAfter_triggered();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual QTableWidget* routeView() const override;
    virtual QTableWidget* pointView() const override;

    virtual QModelIndexList selectedRouteRows() const override;
    virtual QModelIndexList selectedPointRows() const override;

public slots:
    virtual void selectRoute(int row) override;

    virtual void setPolyline(const QString &polyline) override;
    virtual void updateRouteView(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                  RouteTableModel *model) override;
    virtual void updatePointView(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                  PointTableModel *model) override;

    virtual void showErrorMessage(const QString &message) override;

    virtual void setUndoEnabled(bool enable) override;
    virtual void setRedoEnabled(bool enable) override;
};

#endif // MAINWINDOW_H
