#include <QtWidgets>
#include <cmath>


#include "barcreator.h"

const int PaintingScaleFactor = 20;

barCreator::barCreator()
{
    conBar << QPointF(1.5,1.5) << QPointF(0.5,1.5)<<QPointF(0.5,0.5)<<QPointF(1.5,0.5) << QPointF (1.5,1.5);
}

void barCreator::paint(QPainter *painter, const QRect &rect,
                           const QPalette &palette, EditMode mode) const
    {

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    if (mode == Editable) {
        painter->setBrush(palette.highlight());
    } else {
        painter->setBrush(palette.foreground());
    }

    int yOffset = (rect.height() - PaintingScaleFactor) / 2;
    painter->translate(rect.x(), rect.y() + yOffset);
    painter->scale(PaintingScaleFactor, PaintingScaleFactor);

    painter->drawPolygon(conBar, Qt::WindingFill);

    painter->translate(1.0, 0.0);

    painter->restore();
    }

