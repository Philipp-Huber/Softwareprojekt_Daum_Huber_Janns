#include <QtWidgets>


#include "bareditor.h"
#include "barcreator.h"

/*
QSize barEditor::sizeHint() const
{
    return myBar.sizeHint();
}
*/
void barEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    myBar.paint(&painter, rect(), this->palette(),
                       barCreator::Editable);
}

/*int barEditor::barPosition()
{
    int bar = 1;

    return bar;

}*/
