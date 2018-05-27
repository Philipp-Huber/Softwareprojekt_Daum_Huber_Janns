#ifndef STAREDITOR_H
#define STAREDITOR_H

#include <QWidget>

#include "barcreator.h"

class barEditor : public QWidget
{
    Q_OBJECT

public:


    QSize sizeHint() const override;
    void barRating(const barCreator &barcreator) {
        myBar = 1;
    }
    barCreator BarCreator() { return myBar; }


signals:
    void editingFinished();

protected:
     void paintEvent(QPaintEvent *event) override;

private:
    int barPosition();

    barCreator myBar;
};

#endif // BAREDITOR_H
