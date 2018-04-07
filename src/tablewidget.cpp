#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent) :
    QTableWidget(parent)
{  
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

