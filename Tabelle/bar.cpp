#include "bar.h"



bar::bar(QPainter *painter, const QStyleOptionViewItem &option,
const QModelIndex &index)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->setPen(Qt::NoPen);

    painter->setBrush(Qt::green);

    QPolygonF Bar;

    Bar << QPointF(0.4,0.4)<<QPointF(1,0.4)<<QPointF(1,0.6)
        << QPointF(0.4,0.6)<<QPointF(0.4,0.4);

    painter->drawPolygon(Bar,Qt::WindingFill);

    painter->restore();
}
