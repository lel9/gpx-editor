#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    BaseView(parent),
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

    BaseView::connect(ui->tableOfPoints, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_pointChanged(QTableWidgetItem*)));
    BaseView::connect(ui->tableOfRoutes, SIGNAL(itemSelectionChanged()),
            this, SIGNAL(currentRouteChanged()));

    presenter = new Presenter(this);
}

MainWindow::~MainWindow()
{
    delete delegate;
    delete presenter;
    delete ui;
}

QTableWidget *MainWindow::routeView() const
{
    return ui->tableOfRoutes;
}

QTableWidget *MainWindow::pointView() const
{
    return ui->tableOfPoints;
}

QModelIndexList MainWindow::selectedRouteRows() const
{
    return ui->tableOfRoutes->selectionModel()->selectedRows();
}

QModelIndexList MainWindow::selectedPointRows() const
{
    return ui->tableOfPoints->selectionModel()->selectedRows();
}

void MainWindow::selectRoute(int row)
{
    ui->tableOfRoutes->selectRow(row);
}

void MainWindow::setPolyline(const QString &polyline)
{
    ui->textEditPolyline->setText(polyline);
}

void MainWindow::updateRouteView(const QModelIndex &topLeft, const QModelIndex &bottomRight, RouteTableModel *model)
{
    ui->tableOfRoutes->updateModel(topLeft, bottomRight, model);
}

void MainWindow::updatePointView(const QModelIndex &topLeft,
                                 const QModelIndex &bottomRight,
                                 PointTableModel *model)
{
    disconnect(ui->tableOfPoints, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_pointChanged(QTableWidgetItem*)));

    ui->tableOfPoints->updateModel(topLeft, bottomRight, model);
    ui->graphPlot->updateHigh(topLeft, bottomRight, model);

    connect(ui->tableOfPoints, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_pointChanged(QTableWidgetItem*)));
}

void MainWindow::showErrorMessage(const QString &message)
{
    QMessageBox::warning(this, "Ошибка", message);
}

void MainWindow::setUndoEnabled(bool enable)
{
    ui->Undo->setEnabled(enable);
}

void MainWindow::setRedoEnabled(bool enable)
{
    ui->Redo->setEnabled(enable);
}

void MainWindow::on_pointChanged(QTableWidgetItem *item)
{
    emit pointChanged(ui->tableOfPoints->index(item), item->text().toDouble());
}

void MainWindow::on_actionImportGPX_triggered()
{
    //"E://PPO//route_crimea.gpx";
    QString filename = QFileDialog::getOpenFileName(this, tr("Открытие файла"), QDir::currentPath(), "*.gpx");
    emit importFromGPX(filename);
}

void MainWindow::on_actionImportPolyline_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открытие файла"), QDir::currentPath(), "*.txt");
    emit importFromPolyline(filename);
}

void MainWindow::on_actionAddRoute_triggered()
{
    emit addRoute();
}

void MainWindow::on_actionDeleteRoute_triggered()
{
    emit deleteRoute();
}

void MainWindow::on_Undo_triggered()
{
    emit undo();
}

void MainWindow::on_Redo_triggered()
{
    emit redo();
}

void MainWindow::on_actionInsertPointBefore_triggered()
{
    emit insertPoint(Before);
}

void MainWindow::on_actionDeletePoint_triggered()
{
    emit deletePoint();
}

void MainWindow::on_actionInsertPointAfter_triggered()
{
    emit insertPoint(After);
}
