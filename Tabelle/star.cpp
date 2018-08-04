#include "star.h"
#include <cmath>

starDelegate::starDelegate (QObject *parent):
    QStyledItemDelegate(parent)
{
}


void starDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
         float value = index.data().toFloat();
        QColor color;


        //set Star Color
        if (value== 0.0f){
            color = Qt::white;
        }
        else {
            color = Qt::green;
        }

        //Create Star Polygon
            QRect r = option.rect;
            QPolygonF star;
            star << QPointF(30.0, 15);
                for (int i = 1; i < 5; ++i){
                  star << QPointF(15 + 0.5 * (std::cos((-0.2+0.4 * i) * 3.14))*10,
                                         15 + 0.5 *( std::sin((-0.2+0.4 * i) * 3.14))*10);
                  star << QPointF(15 + std::cos(0.4 * i * 3.14)*15,
                                           15 +  std::sin(0.4 * i * 3.14)*15);

                 }
                star << QPointF(15 + 0.5 * (std::cos((-0.2+0.4 * 5) * 3.14))*10,
                                     15 + 0.5 *( std::sin((-0.2+0.4 * 5) * 3.14))*10);


            // Draw Stars
            painter->save();

            QPen pen(Qt::SolidLine);
            pen.setColor(Qt::black);
            pen.setWidth(1);
            painter->setPen(pen);
            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->translate(r.x(),r.y()+6);
            painter->rotate(-18);
            painter->setBrush(QBrush(color));
            painter->drawPolygon(star,Qt::WindingFill);

            painter->restore();



}



















