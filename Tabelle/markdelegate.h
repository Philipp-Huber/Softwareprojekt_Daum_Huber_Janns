#ifndef MARKDELEGATE_H
#define MARKDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QtMath>

class markDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    markDelegate(QWidget *parent = 0 ) : QStyledItemDelegate(parent){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // MARKDELEGATE_H
