#include <QtWidgets>
#include <cmath>


#include "barcreator.h"

const int PaintingScaleFactor = 20;
const int penWidth = 0;
const qreal barLength = 4;
const qreal barHeight = 1;
const qreal leftX = 0.5;
const qreal bottomY = 0.5;

barCreator::barCreator()
{
    conBar << QPointF((leftX + barLength), (bottomY + barHeight)) << QPointF (leftX, (bottomY + barHeight))
           << QPointF(leftX, bottomY) << QPointF((leftX + barLength), bottomY)
           << QPointF((leftX + barLength), (bottomY + barHeight));

    percentageFilled = 0;

}
barCreator::barCreator(int percentage){
    conBar << QPointF((leftX + barLength), (bottomY + barHeight)) << QPointF (leftX, (bottomY + barHeight))
           << QPointF(leftX, bottomY) << QPointF((leftX + barLength), bottomY)
           << QPointF((leftX + barLength), (bottomY + barHeight));

    percentageFilled = percentage;
}

void barCreator::paint(QPainter *painter, const QRect &rect,
                           const QPalette &palette, EditMode mode) const
    {

    painter->save();

    //makes the frame of the bar
    painter->setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::SolidLine);
    pen.setColor(Qt::black);
    pen.setWidth(penWidth);
    painter->setPen(pen);
    //fills the bar
    painter->fillRect(leftX, bottomY, PaintingScaleFactor*(barLength*(percentageFilled/100)),PaintingScaleFactor * barHeight, Qt::green);

//    if (mode == Editable) {
//        painter->setBrush(palette.highlight());
//    } else {
//        painter->setBrush(palette.foreground());
//    }

//  positions the bar
    int yOffset = (barHeight - PaintingScaleFactor) / 2;
    painter->translate(rect.x(), rect.y() + yOffset);
    painter->scale(PaintingScaleFactor, PaintingScaleFactor);

    painter->drawPolygon(conBar, Qt::WindingFill);

    painter->translate(1.0, 0.0);

    painter->restore();
    }

