#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent) :
    QTableWidget(parent)
{  
}

TableWidget::TableWidget(const TableWidget &other) :
    QTableWidget()
{
    int row = other.rowCount();
    int column = other.columnCount();
    this->setRowCount(row);
    this->setColumnCount(column);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::DisplayRole, other.item(i, j)->data(Qt::DisplayRole));
            this->setItem(i, j, item);
        }
    }

    this->setSelectionBehavior(other.selectionBehavior());
    this->setSelectionMode(other.selectionMode());
    for (auto r : other.selectionModel()->selectedRows())
        this->selectRow(r.row());
}

TableWidget::~TableWidget()
{
}

QVariant TableWidget::getData(const TableIndex &index)
{
    if (index.row() >= rowCount() || index.column() >= columnCount())
        return QVariant();
    QTableWidgetItem *item = this->item(index.row(), index.column());
    if (!item)
        return QVariant();
    return item->data(Qt::DisplayRole);
}

void TableWidget::setData(const TableIndex &index, const QVariant &data)
{
    int col = index.column();
    int row = index.row();
    if (columnCount() <= col)
        setColumnCount(col + 1);
    if (rowCount() <= row)
        setRowCount(row + 1);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(Qt::DisplayRole, data);
    setItem(row, col, item);
}

TableIndex TableWidget::index(QTableWidgetItem *item) const
{
    QModelIndex qIndex = indexFromItem(item);
    return TableIndex(qIndex.row(), qIndex.column());
}

TableWidget &TableWidget::operator=(const TableWidget &other)
{
    int row = other.rowCount();
    int column = other.columnCount();
    this->setRowCount(row);
    this->setColumnCount(column);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::DisplayRole, other.item(i,j)->data(Qt::DisplayRole));
            this->setItem(i, j, item);
        }
    }

    this->setSelectionBehavior(other.selectionBehavior());
    this->setSelectionMode(other.selectionMode());
    this->clearSelection();
    for (auto r : other.selectionModel()->selectedRows())
        this->selectRow(r.row());

    return *this;
}

bool operator==(const TableWidget &first, const TableWidget &second)
{
    if (first.rowCount() != second.rowCount())
        return false;
    if (first.columnCount() != second.columnCount())
        return false;
    if (first.selectedIndexes() != second.selectedIndexes())
        return false;

    int row = first.rowCount();
    int column = first.colorCount();
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            if (first.item(i, j)->text() != second.item(i, j)->text())
                return false;

    return true;
}

bool operator!=(const TableWidget &first, const TableWidget &second)
{
    return !(first == second);
}

