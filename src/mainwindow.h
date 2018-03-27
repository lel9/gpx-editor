#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QTableWidget>

#include <memory>
using namespace std;

#include "route_loader.h"
#include "route_table_model.h"
#include "add_route_command.h"
#include "remove_route_command.h"
#include "add_point_command.h"
#include "remove_point_command.h"
#include "edit_point_command.h"

#include "table_point_item_delegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    shared_ptr<RouteTableModel> model;
    PointTableModel nullModel;
    TablePointItemDelegate *delegate;

    QStack<shared_ptr<Command>> commandUndoStack;
    QStack<shared_ptr<Command>> commandRedoStack;

    QString dataPath;

private:
    void getDataPath();

    void importRoute(shared_ptr<RouteLoader> loader);
    void showRoute(const shared_ptr<Route> &route);
    void insertRoute(int pos, const shared_ptr<Route> &route);

    bool hasSelected(const QTableView *view);
    int selectedRow(const QTableView *view);

    void executeCommand(shared_ptr<Command> command);

private slots:
    void on_pointEdit(int row, QGeoCoordinate newPoint);
    void routesSelectionChanged(QItemSelection selected, QItemSelection deselected);
    void routesRemoved(const QModelIndex &parent, int first, int last);
    void routesAboutToBeRemoved(const QModelIndex &parent, int first, int last);
    void routesInserted(const QModelIndex &parent, int first, int last);

    void on_actionImportGPX_triggered();
    void on_actionImportPolyline_triggered();

    void on_actionAddRoute_triggered();
    void on_actionDeleteRoute_triggered();

    void on_Undo_triggered();
    void on_Redo_triggered();

    void on_actionInsertPointBefore_triggered();
    void on_actionDeletePoint_triggered();
    void on_actionInsertPointAfter_triggered();

    void on_buttonUpdate_clicked();

protected:
    virtual void closeEvent(QCloseEvent *);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
