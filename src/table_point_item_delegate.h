#ifndef TABLEPOINTITEMDELEGATE_H
#define TABLEPOINTITEMDELEGATE_H

#include <QItemDelegate>

class TablePointItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    TablePointItemDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

signals:
    void editPoint(QAbstractItemModel*, QModelIndex);

};

#endif // TABLEPOINTITEMDELEGATE_H
