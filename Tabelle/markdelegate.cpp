#include <QApplication>
#include <QtWidgets/QTableView>
#include "markdelegate.h"


void markDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.data().canConvert<float>()) {
        //Initiating Varibles and Constans
        int baseNum = 2;
        double width = 0.1;
        int maxFactor = 14;
        int redFactor = 6;
        int yellowFactor = 8;
        double offsetConstent1 = 0.05;
        double offsetConstent2 = 0.8;
        double offsetConstent3 = 0.75;
        double offsetConstent4 = 0.5;
        qreal value = index.data().toDouble();
        qreal workingNum = qLn(value)/qLn(baseNum);
        QColor color = Qt::green;

        //determening Color
        if(workingNum/maxFactor > 1){
            workingNum = maxFactor;
            color = Qt::blue;
        }
        else if(workingNum < 0){
            workingNum = 0;
        }
        else if (workingNum < redFactor){
            color = Qt::red;
        }
        else if (workingNum < yellowFactor){
            color = Qt::yellow;
        }

        //Create rect to paint
        QRect marker = option.rect;
        qreal offset = (workingNum)/maxFactor;
        //Adjust base rect so it isn't flush with the marker borders
        marker.setWidth(marker.width() * width);
        marker.moveLeft(option.rect.left() + offsetConstent1*option.rect.width()+ offsetConstent2*offset*option.rect.width()); //Move right -> add
        marker.setHeight(marker.height() * offsetConstent3);
        marker.moveBottom(option.rect.bottom() - offsetConstent4 * (option.rect.height() - marker.height())); // Move up -> subtract


        //Paint the Marker
        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::black);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->setBrush(QBrush(color));
        painter->drawRect(marker);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }


}
