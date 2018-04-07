#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent) :
    QTableWidget(parent)
{  
}

TableWidget::TableWidget(const TableWidget &other)
{
    int row= other.rowCount();
    int column = other.colorCount();
    this->setRowCount(row);
    this->setColumnCount(column);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            this->setItem(i, j, other.item(i, j));
}

TableWidget::~TableWidget()
{
}

void TableWidget::updateModel(const QModelIndex &topLeft,
                              const QModelIndex &bottomRight,
                              QAbstractItemModel *model)
{
    this->setRowCount(model->rowCount());
    int column = model->columnCount();
    this->setColumnCount(column);

    QStringList list;
    for (int i = 0; i < column; i++)
        list << model->headerData(i, Qt::Horizontal).toString();
    this->setHorizontalHeaderLabels(list);

    if (topLeft.isValid() && bottomRight.isValid())
    {
        int iBegin = topLeft.row();
        int iEnd = bottomRight.row();
        int jBegin = topLeft.column();
        int jEnd = bottomRight.column();

        for (int i = iBegin; i <= iEnd; i++)
        {
            for (int j = jBegin; j <= jEnd; j++)
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                item->setData(Qt::DisplayRole, model->data(model->index(i,j)));
                this->setItem(i,j,item);
            }
        }
    }
}

QModelIndex TableWidget::index(QTableWidgetItem *item) const
{
    return indexFromItem(item);
}

TableWidget &TableWidget::operator=(const TableWidget &other)
{
    int row= other.rowCount();
    int column = other.colorCount();
    this->setRowCount(row);
    this->setColumnCount(column);
    this->setSelectionModel(other.selectionModel());

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            this->setItem(i, j, other.item(i, j));

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

