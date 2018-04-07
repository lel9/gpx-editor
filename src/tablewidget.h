#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QAbstractItemModel>

class TableWidget : public QTableWidget
{
public:
    TableWidget(QWidget *parent = 0);
    ~TableWidget();
    void updateModel(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     QAbstractItemModel *model);
    QModelIndex index(QTableWidgetItem *item) const;
};

#endif // TABLEWIDGET_H
