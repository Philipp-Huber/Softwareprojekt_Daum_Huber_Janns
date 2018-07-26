#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class barDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    barDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

};



#endif // BARDELEGATE_H
