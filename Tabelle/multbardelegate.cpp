#include <QApplication>
#include <QtWidgets/QTableView>
#include "multbardelegate.h"

void multBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.data().canConvert<float>()) {
        // Initiation Variables and Contans
        int baseNum = 2;
        double offsetConstent1 = 0.75;
        double offsetConstent2 = 0.9;
        double offsetConstent3 = 0.05;
        bool toBig = false;
        double heightOffset = 0.125;
        int maxNum = 8;
        int redNum = 3;
        int yellowNum = 5;
        qreal value = index.data().toDouble();
        qreal workingNum = qLn(value)/qLn(baseNum);
        QRect redRect =  option.rect;
        QRect yellowRect = option.rect;
        QRect greenRect =  option.rect;
        QRect blueRect =  option.rect;


        // Initiate Rectangels


        redRect.setHeight(redRect.height() * offsetConstent1);
        redRect.moveBottom(option.rect.bottom() - heightOffset * (option.rect.height())); // Move up -> subtract
        redRect.moveLeft(option.rect.left() + offsetConstent3 * option.rect.width()); //Move right -> add


        yellowRect.setHeight(yellowRect.height() * offsetConstent1);
        yellowRect.moveBottom(option.rect.bottom() - heightOffset * (option.rect.height())); // Move up -> subtract
        yellowRect.moveLeft(option.rect.left() + (offsetConstent3 + (redNum * offsetConstent2/maxNum)) * option.rect.width());

        greenRect.setHeight(greenRect.height() * offsetConstent1);
        greenRect.moveBottom(option.rect.bottom() - heightOffset * (option.rect.height())); // Move up -> subtract
        greenRect.moveLeft(option.rect.left() + (offsetConstent3 + (yellowNum * offsetConstent2/maxNum) * offsetConstent2) * option.rect.width());

        blueRect.setHeight(blueRect.height() * offsetConstent1);
        blueRect.setWidth(blueRect.width() * offsetConstent2);
        blueRect.moveBottom(option.rect.bottom() - heightOffset * (option.rect.height())); // Move up -> subtract
        blueRect.moveLeft(option.rect.left() + offsetConstent3 * (option.rect.width())); //Move right -> add



// Size Rectangels acording to data
        if(workingNum > maxNum || workingNum < 0){
            workingNum = maxNum;

            toBig=true;
            redRect.setWidth(0);
            greenRect.setWidth(0);
            yellowRect.setWidth(0);
        }
        else if (workingNum<=redNum){
            greenRect.setWidth(0);
            yellowRect.setWidth(0);
            redRect.setWidth(redRect.width() * workingNum*offsetConstent2/maxNum);
        }
        else if (workingNum<=yellowNum && workingNum>redNum){  
            greenRect.setWidth(0);
            yellowRect.setWidth(yellowRect.width() * ((workingNum-redNum)*offsetConstent2/maxNum));
            redRect.setWidth(redRect.width() * (redNum*offsetConstent2/maxNum));
        }
        else{    
            greenRect.setWidth(greenRect.width() * ((workingNum-yellowNum) * offsetConstent2 * 1/maxNum));
            yellowRect.setWidth(yellowRect.width() * ((yellowNum-redNum) * offsetConstent2/maxNum));
            redRect.setWidth(redRect.width() * (redNum * offsetConstent2/maxNum)) ;
        }

        // paint Reacts

        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::black);
        pen.setWidth(2);
        painter->setPen(pen);

        painter->setBrush(QBrush(Qt::green));
        painter->drawRect(greenRect);
        painter->setBrush(QBrush(Qt::yellow));
        painter->drawRect(yellowRect);
        painter->setBrush(QBrush(Qt::red));
        painter->drawRect(redRect);
        if (toBig){
        painter->setBrush(QBrush(Qt::blue));
        painter->drawRect(blueRect);
        }
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }


}
