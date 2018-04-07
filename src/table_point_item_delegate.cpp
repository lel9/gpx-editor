#include "table_point_item_delegate.h"

#include <QDoubleSpinBox>

TablePointItemDelegate::TablePointItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *TablePointItemDelegate::createEditor(QWidget *parent,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const
{
    QWidget *w = QItemDelegate::createEditor(parent, option, index);

    if (QDoubleSpinBox *sb = qobject_cast<QDoubleSpinBox *>(w))
    {
        sb->setDecimals(5);
        sb->setSingleStep(1);
    }
    return w;
}

#include <QEvent>
bool TablePointItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                         const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::Enter)
        emit editPoint(model, index);

    return QItemDelegate::editorEvent(event, model, option, index);
}
