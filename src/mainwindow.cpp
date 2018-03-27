#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableOfRoutes->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableOfRoutes->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableOfPoints->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableOfPoints->setSelectionBehavior(QAbstractItemView::SelectRows);

    delegate = new TablePointItemDelegate;
    ui->tableOfPoints->setItemDelegate(delegate);

    ui->Undo->setEnabled(false);
    ui->Redo->setEnabled(false);

    model = make_shared<RouteTableModel>();

    getDataPath();

    shared_ptr<RouteLoader> loader = make_shared<PolylineLoader>();
    try
    {
        loader->setFileName(dataPath);
        QVector<shared_ptr<Route>> routes = loader->load();
        for (auto route : routes)
            insertRoute(model->rowCount(), route);
    }
    catch (std::exception &) { }

    RouteTableModel *modelPtr = model.get();
    ui->tableOfRoutes->setModel(modelPtr);
    connect(ui->tableOfRoutes->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(routesSelectionChanged(QItemSelection,QItemSelection)));
    connect(modelPtr, SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this, SLOT(routesRemoved(QModelIndex,int,int)));
    connect(modelPtr, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
            this, SLOT(routesAboutToBeRemoved(QModelIndex,int,int)));
    connect(modelPtr, SIGNAL(rowsInserted(QModelIndex,int,int)),
            this, SLOT(routesInserted(QModelIndex,int,int)));
}

MainWindow::~MainWindow()
{
    delete delegate;
    delete ui;
}

#include <QStandardPaths>
void MainWindow::getDataPath()
{
    dataPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QDir dir(dataPath);
    if (!dir.exists())
        dir.mkpath(dataPath);
    dataPath = dir.absoluteFilePath("routes.xml");
}

void MainWindow::importRoute(shared_ptr<RouteLoader> loader)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открытие файла"), QDir::currentPath());
    if (!filename.isEmpty())
    {
        try
        {
            loader->setFileName(filename);
            QVector<shared_ptr<Route>> routes = loader->load();
            for (auto route : routes)
                insertRoute(model->rowCount(), route);
        }
        catch (std::exception &ex)
        {
            QMessageBox::warning(this, "Ошибка", QString(ex.what()));
        }
    }
}

void MainWindow::executeCommand(shared_ptr<Command> command)
{
    if (command->execute() == 0)
    {
        commandUndoStack.push(command);
        ui->Undo->setEnabled(true);
    }
}

void MainWindow::on_pointEdit(int row, QGeoCoordinate newPoint)
{
    shared_ptr<Command> command = make_shared<EditPointCommand>(row, newPoint, model->currentRoute());
    executeCommand(command);
}

bool MainWindow::hasSelected(const QTableView *view)
{
    if (view->selectionModel() != nullptr)
        return !(view->selectionModel()->selectedRows().isEmpty());
    return false;
}

int MainWindow::selectedRow(const QTableView *view)
{
    if (hasSelected(view))
        return view->selectionModel()->selectedRows()[0].row();
    return -1;
}

void MainWindow::showRoute(const shared_ptr<Route> &route)
{
    try
    {
        ui->textEditPolyline->setText(model->currentRoute()->polyline());
    }
    catch (std::exception &ex)
    {
        QMessageBox::warning(this, "Ошибка", QString(ex.what()));
    }

    ui->tableOfPoints->setModel(route->model().get());
}

void MainWindow::insertRoute(int pos, const shared_ptr<Route> &route)
{
    executeCommand(make_shared<AddRouteCommand>(pos, route, model));
    connect(route->model().get(), SIGNAL(pointEdit(int,QGeoCoordinate)),
            this, SLOT(on_pointEdit(int,QGeoCoordinate)));
}

void MainWindow::routesSelectionChanged(QItemSelection selected, QItemSelection deselected)
{
    Q_UNUSED(deselected)

    if (!selected.isEmpty())
    {
        model->setCurrentRoute(selected[0].topLeft().row());
        showRoute(model->currentRoute());
    }
}

void MainWindow::routesRemoved(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    Q_UNUSED(first)
    Q_UNUSED(last)

    ui->tableOfPoints->setModel(nullptr);
    ui->textEditPolyline->clear();
    ui->tableOfRoutes->selectionModel()->blockSignals(false);

    // выделяем 1- ю строку
    ui->tableOfRoutes->clearSelection();
    if (model->rowCount() != 0)
        ui->tableOfRoutes->selectRow(0);
}

void MainWindow::routesAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    Q_UNUSED(first)
    Q_UNUSED(last)
    ui->tableOfRoutes->selectionModel()->blockSignals(true);
}

void MainWindow::routesInserted(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    Q_UNUSED(last)
    ui->tableOfRoutes->selectRow(first);
}

void MainWindow::on_actionImportGPX_triggered()
{
    shared_ptr<RouteLoader> loader = make_shared<GPXLoader>();
    importRoute(loader);
}

void MainWindow::on_actionImportPolyline_triggered()
{
    shared_ptr<RouteLoader> loader = make_shared<PolylineLoader>();
    importRoute(loader);

}

void MainWindow::on_actionAddRoute_triggered()
{
    shared_ptr<Route> route = make_shared<Route>();
    insertRoute(model->rowCount(), route);
}

void MainWindow::on_actionDeleteRoute_triggered()
{
    if (hasSelected(ui->tableOfRoutes))
    {
        int row = selectedRow(ui->tableOfRoutes);
        executeCommand(make_shared<RemoveRouteCommand>(row, model));
    }
}

void MainWindow::on_Undo_triggered()
{
    shared_ptr<Command> command = commandUndoStack.pop();
    if (command->unExecute() == 0)
    {
        commandRedoStack.push(command);
        ui->Redo->setEnabled(true);
        if (commandUndoStack.isEmpty())
            ui->Undo->setEnabled(false);
    }
}

void MainWindow::on_Redo_triggered()
{
    shared_ptr<Command> command = commandRedoStack.pop();
    if (command->execute() == 0)
    {
        commandUndoStack.push(command);
        ui->Undo->setEnabled(true);
        if (commandRedoStack.isEmpty())
            ui->Redo->setEnabled(false);
    }
}

void MainWindow::on_actionInsertPointBefore_triggered()
{
    if (hasSelected(ui->tableOfRoutes))
    {
        if (hasSelected(ui->tableOfPoints))
        {
            int row = selectedRow(ui->tableOfPoints);
            executeCommand(make_shared<AddPointCommand>(row, model->currentRoute()));
        }
        else if (ui->tableOfPoints->model()->rowCount() == 0)
            executeCommand(make_shared<AddPointCommand>(0, model->currentRoute()));
    }
}

void MainWindow::on_actionDeletePoint_triggered()
{
    if (hasSelected(ui->tableOfRoutes) && hasSelected(ui->tableOfPoints))
    {
        int row = selectedRow(ui->tableOfPoints);
        executeCommand(make_shared<RemovePointCommand>(row, model->currentRoute()));
    }
}

void MainWindow::on_actionInsertPointAfter_triggered()
{
    if (hasSelected(ui->tableOfRoutes))
    {
        if (hasSelected(ui->tableOfPoints))
        {
            int row = selectedRow(ui->tableOfPoints) + 1;
            executeCommand(make_shared<AddPointCommand>(row, model->currentRoute()));
        }
        else if (ui->tableOfPoints->model()->rowCount() == 0)
            executeCommand(make_shared<AddPointCommand>(0, model->currentRoute()));
    }
}

void MainWindow::on_buttonUpdate_clicked()
{
    try
    {
        ui->textEditPolyline->setText(model->currentRoute()->polyline());
    }
    catch (std::exception &ex)
    {
        QMessageBox::warning(this, "Ошибка", QString(ex.what()));
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
    shared_ptr<RouteSaver> saver = make_shared<SimpleRouteSaver>();
    saver->setFileName(dataPath);
    try
    {
        model->saveRoutes(saver);
    }
    catch (std::exception &ex)
    {

    }
}
