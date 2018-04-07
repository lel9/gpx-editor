#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include <QAbstractItemModel>

class TableWidget : public QTableWidget
{
public:
    TableWidget(QWidget *parent = 0);
    TableWidget(const TableWidget &other);
    ~TableWidget();
    void updateModel(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     QAbstractItemModel *model);
    QModelIndex index(QTableWidgetItem *item) const;

    TableWidget& operator=(const TableWidget &other);

    // для тестов
    friend bool operator==(const TableWidget &first, const TableWidget &second);
    friend bool operator!=(const TableWidget &first, const TableWidget &second);
};

#endif // TABLEWIDGET_H
