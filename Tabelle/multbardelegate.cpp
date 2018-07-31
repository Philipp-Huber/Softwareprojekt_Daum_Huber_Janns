#include <QApplication>
#include <QtWidgets/QTableView>
#include "multbardelegate.h"

void multBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.data().canConvert<float>()) {
        //Get data and error correction (for drawing only)
        qreal value = index.data().toDouble();
        qreal workingNum = qLn(value)/qLn(2);
        QRect r = option.rect;
        bool toBig = false;

        // Define Constance
        double heightOffset = 0.125;
        int maxNum = 8;
        int redNum = 3;
        int yellowNum = 5;

        // Initiate Rectangels
        QRect redRect = r;
        redRect.setWidth(0);
        redRect.setHeight(r.height() * 0.75);
        redRect.moveBottom(option.rect.bottom() - heightOffset * (option.rect.height())); // Move up -> subtract
        QRect yellowRect =r;
        yellowRect.setWidth(0);
        yellowRect.setHeight(r.height() * 0.75);
        yellowRect.moveBottom(option.rect.bottom() - heightOffset * (option.rect.height())); // Move up -> subtract
        QRect greenRect = r;
        greenRect.setWidth(0);
        greenRect.setHeight(r.height() * 0.75);
        greenRect.moveBottom(option.rect.bottom() - heightOffset * (option.rect.height())); // Move up -> subtract
        QRect blueRect = r;
        blueRect.setWidth(0);
        blueRect.setHeight(r.height() * 0.75);
        blueRect.moveBottom(option.rect.bottom() - heightOffset * (option.rect.height())); // Move up -> subtract




// Size Rectangels acording to data
        if(workingNum > maxNum){
            workingNum = maxNum;

            toBig=true;
            blueRect.setWidth(r.width() * 0.9);
            blueRect.moveLeft(option.rect.left() + 0.05 * (option.rect.width())); //Move right -> add


        } else if(workingNum < 0){

            redRect.setWidth(r.width() *0);
            redRect.moveLeft(option.rect.left() + 0.05*option.rect.width()); //Move right -> add

        }
        else if (workingNum<=redNum){


            redRect.setWidth(r.width() * workingNum/10);
            redRect.moveLeft(option.rect.left() + 0.05*option.rect.width()); //Move right -> add


        }
        else if (workingNum<=yellowNum && workingNum>redNum){


            redRect.setWidth(r.width() * (redNum*0.9/10));
            redRect.moveLeft(option.rect.left() + 0.05*option.rect.width()); //Move right -> add



            yellowRect.setWidth(r.width() * ((workingNum-redNum)*0.9/10));
            yellowRect.moveLeft(option.rect.left() + (0.05+(redNum*0.9/10))*option.rect.width()); //Move right -> add

        }
        else
        {


            redRect.setWidth(r.width() * (redNum*0.9/10)) ;
            redRect.moveLeft(option.rect.left() + 0.05*option.rect.width()); //Move right -> add


            yellowRect.setWidth(r.width() * ((yellowNum-redNum)*0.9/10));
            yellowRect.moveLeft(option.rect.left() + (0.05+(redNum*0.9/10))*option.rect.width()); //Move right -> add

            greenRect.setWidth(r.width() * ((workingNum-yellowNum)*0.9/10));
            greenRect.moveLeft(option.rect.left() + (0.05+(yellowNum*0.9/10)*0.9)*option.rect.width()); //Move right -> add

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
