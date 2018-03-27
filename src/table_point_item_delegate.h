#ifndef TABLEPOINTITEMDELEGATE_H
#define TABLEPOINTITEMDELEGATE_H

#include <QItemDelegate>

class TablePointItemDelegate : public QItemDelegate
{
public:
    TablePointItemDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
};

#endif // TABLEPOINTITEMDELEGATE_H
