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

    connect(ui->tableOfPoints, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_pointChanged(QTableWidgetItem*)));
    connect(ui->tableOfRoutes, SIGNAL(itemSelectionChanged()),
            this, SIGNAL(currentRouteChanged()));

    connect(ui->tableOfRoutes, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_routeChanged(QTableWidgetItem*)));

    presenter = new Presenter(this);
    presenter->recoverRoutes();
}

MainWindow::~MainWindow()
{
    delete delegate;
    delete presenter;
    delete ui;
}

int MainWindow::selectedRouteRow() const
{
    QModelIndexList rows = ui->tableOfRoutes->selectionModel()->selectedRows();
    if (!rows.isEmpty())
        return rows[0].row();
    return -1;
}

int MainWindow::selectedPointRow() const
{
    QModelIndexList rows = ui->tableOfPoints->selectionModel()->selectedRows();
    if (!rows.isEmpty())
        return rows[0].row();
    return -1;
}

QString MainWindow::polyline() const
{
    return ui->textEditPolyline->toPlainText();
}

QVariant MainWindow::routeData(const TableIndex &index) const
{
    return ui->tableOfRoutes->getData(index);
}

QVariant MainWindow::pointData(const TableIndex &index) const
{
    return ui->tableOfPoints->getData(index);
}

int MainWindow::routeViewRow() const
{
    return ui->tableOfRoutes->rowCount();
}

int MainWindow::pointViewRow() const
{
    return ui->tableOfPoints->rowCount();
}

int MainWindow::routeViewColumn() const
{
    return ui->tableOfRoutes->columnCount();
}

int MainWindow::pointViewColumn() const
{
    return ui->tableOfPoints->columnCount();
}

QVector<double> MainWindow::plotKeys() const
{
    return ui->graphPlot->keys();
}

QVector<double> MainWindow::plotValues() const
{
    return ui->graphPlot->values();
}

BaseView *MainWindow::copy()
{
    return nullptr;
}

void MainWindow::selectRoute(int row)
{
    ui->tableOfRoutes->clearSelection();
    ui->tableOfRoutes->selectRow(row);
}

void MainWindow::selectPoint(int row)
{
    ui->tableOfPoints->clearSelection();
    ui->tableOfPoints->selectRow(row);
}

void MainWindow::setPolyline(const QString &polyline)
{
    ui->textEditPolyline->setText(polyline);
}

void MainWindow::setRouteViewSize(int rowCount, int columnCount)
{
    ui->tableOfRoutes->setRowCount(rowCount);
    ui->tableOfRoutes->setColumnCount(columnCount);
}

void MainWindow::setPointViewSize(int rowCount, int columnCount)
{
    ui->tableOfPoints->setRowCount(rowCount);
    ui->tableOfPoints->setColumnCount(columnCount);
}

void MainWindow::setRouteViewHeaders(const QStringList &header)
{
    ui->tableOfRoutes->setHorizontalHeaderLabels(header);
}

void MainWindow::setPointViewHeaders(const QStringList &header)
{
    ui->tableOfPoints->setHorizontalHeaderLabels(header);
}

void MainWindow::updateRouteView(const TableIndex &index, const QVariant &data)
{
    disconnect(ui->tableOfRoutes, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_routeChanged(QTableWidgetItem*)));

    ui->tableOfRoutes->setData(index, data);

    connect(ui->tableOfRoutes, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_routeChanged(QTableWidgetItem*)));
}

void MainWindow::updatePointView(const TableIndex &index, const QVariant &data)
{
    disconnect(ui->tableOfPoints, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_pointChanged(QTableWidgetItem*)));

    ui->tableOfPoints->setData(index, data);

    connect(ui->tableOfPoints, SIGNAL(itemChanged(QTableWidgetItem*)),
            this, SLOT(on_pointChanged(QTableWidgetItem*)));
}

void MainWindow::setPlotData(const QVector<double> &keys, const QVector<double> &values)
{
    ui->graphPlot->setPlotData(keys, values);
}

void MainWindow::showErrorMessage(const QString &message)
{
    QMessageBox::warning(this, "Ошибка", message);
}

void MainWindow::setOperationResult(const QString &result)
{
    ui->operationResult->setText(result);
}

void MainWindow::addOperation(const QString &name)
{
    ui->operationList->addItem(name);
}

void MainWindow::removeOperation(int index)
{
    ui->operationList->removeItem(index);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    presenter->saveRoutes();
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
    presenter->on_pointChanged(ui->tableOfPoints->index(item), item->text().toDouble());
}

void MainWindow::on_routeChanged(QTableWidgetItem *item)
{
    if (item->column() == 0)
        presenter->on_routeNameChanged(item->text());
}

void MainWindow::on_actionImportGPX_triggered()
{
    //"E://PPO//route_crimea.gpx";
    QString filename = QFileDialog::getOpenFileName(this, tr("Открытие файла"), QDir::currentPath(), "*.gpx");
    presenter->on_importFromGPX(filename);
}

void MainWindow::on_actionImportPolyline_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открытие файла"), QDir::currentPath(), "*.txt");
    presenter->on_importFromPolyline(filename);
}

void MainWindow::on_actionAddRoute_triggered()
{
    presenter->on_addRoute();
}

void MainWindow::on_actionDeleteRoute_triggered()
{
    presenter->on_deleteRoute();
}

void MainWindow::on_Undo_triggered()
{
    presenter->on_undo();
}

void MainWindow::on_Redo_triggered()
{
    presenter->on_redo();
}

void MainWindow::on_actionInsertPointBefore_triggered()
{
    presenter->on_insertPoint(Before);
}

void MainWindow::on_actionDeletePoint_triggered()
{
    presenter->on_deletePoint();
}

void MainWindow::on_actionInsertPointAfter_triggered()
{
    presenter->on_insertPoint(After);
}

void MainWindow::on_pushButton_clicked()
{
    presenter->executeOperaton(ui->operationList->currentIndex());
}
