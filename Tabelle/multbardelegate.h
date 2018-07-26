#ifndef MULTBARDELEGATE_H
#define MULTBARDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QtMath>

class multBarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    multBarDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

 };

#endif // MULTBARDELEGATE_H
