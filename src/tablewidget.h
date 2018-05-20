#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>
#include "table_index.h"

class TableWidget : public QTableWidget
{
public:
    TableWidget(QWidget *parent = 0);
    TableWidget(const TableWidget &other);
    ~TableWidget();
    QVariant getData(const TableIndex &index);
    void setData(const TableIndex &index, const QVariant &data);
    TableIndex index(QTableWidgetItem *item) const;

    TableWidget& operator=(const TableWidget &other);

    // для тестов
    friend bool operator==(const TableWidget &first, const TableWidget &second);
    friend bool operator!=(const TableWidget &first, const TableWidget &second);
};

#endif // TABLEWIDGET_H
