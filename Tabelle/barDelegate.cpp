#include <QApplication>
#include <QtWidgets/QTableView>
#include "barDelegate.h"


void barDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        if (index.data().canConvert<float>()) {
            //Initating Constans
            double offsetConstent1 = 0.9;
            double offsetConstent2 = 0.5;
            double offsetConstent3 = 0.75;

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
            QRect bar = option.rect;
            //Adjust base rect so it isn't flush with the bar borders
            bar.setWidth(bar.width() * offsetConstent1);
            bar.moveLeft(option.rect.left() + offsetConstent2 * (option.rect.width() - bar.width())); //Move right -> add
            bar.setHeight(bar.height() * offsetConstent3);
            bar.moveBottom(option.rect.bottom() - offsetConstent2 * (option.rect.height() - bar.height())); // Move up -> subtract
            //Set final width
            bar.setWidth(bar.width() * value);
            //Paint the bars
            QPen pen(Qt::SolidLine);
            pen.setColor(Qt::black);
            pen.setWidth(2);
            painter->setPen(pen);
            painter->setBrush(QBrush(color));
            painter->drawRect(bar);
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }

}
