#include <QApplication>
#include <QtWidgets/QTableView>
#include "barDelegate.h"


void barDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        if (index.data().canConvert<float>()) {
            //Get data and error correction (for drawing only)
            float value = index.data().toFloat();
            QColor color = Qt::green;
            if(value > 1){
                value = 1;
                color = Qt::blue;
            } else if(value < 0){
                value = 0;
            }
            //Create rect to paint
            QRect r = option.rect;
            //Adjust base rect so it isn't flush with the cell borders
            r.setWidth(r.width() * 0.9);
            r.moveLeft(option.rect.left() + 0.5 * (option.rect.width() - r.width())); //Move right -> add
            r.setHeight(r.height() * 0.75);
            r.moveBottom(option.rect.bottom() - 0.5 * (option.rect.height() - r.height())); // Move up -> subtract
            //Set final width
            r.setWidth(r.width() * value);
            //Paint the bars
            QPen pen(Qt::SolidLine);
            pen.setColor(Qt::black);
            pen.setWidth(2);
            painter->setPen(pen);
            painter->setBrush(QBrush(color));
            painter->drawRect(r);
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }

}
