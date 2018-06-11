#ifndef BAR_H
#define BAR_H
#include<QStyledItemDelegate>
#include<QPainter>
#include <QPointF>
#include <QVector>

class bar :public QStyledItemDelegate
{
    Q_OBJECT
public:
     bar(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index);
};

#endif // BAR_H
