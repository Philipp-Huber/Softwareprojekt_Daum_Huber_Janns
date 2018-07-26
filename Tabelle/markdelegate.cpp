#include <QApplication>
#include <QtWidgets/QTableView>
#include "markdelegate.h"


void markDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.data().canConvert<float>()) {
        //Get data and error correction (for drawing only)
        qreal value = index.data().toDouble();
        qreal workingNum = qLn(value)/qLn(2);

        QColor color = Qt::green;
        if(workingNum/14 > 1){
            workingNum = 14;
            color = Qt::blue;
        } else if(workingNum < 0){
            workingNum = 0;
        }
        else if (workingNum<5.3){
            color = Qt::red;
        }
        else if (workingNum<8){
            color = Qt::yellow;
        }

        //Create rect to paint
        QRect r = option.rect;
        qreal offset = (workingNum)/14;
        //Adjust base rect so it isn't flush with the cell borders
        r.setWidth(r.width() * 0.1);
        r.moveLeft(option.rect.left() + 0.05*option.rect.width()+ 0.8*offset*option.rect.width()); //Move right -> add
        r.setHeight(r.height() * 0.75);
        r.moveBottom(option.rect.bottom() - 0.5 * (option.rect.height() - r.height())); // Move up -> subtract
        //Set final width
        //r.setWidth(r.width() * value);
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
