#include "booleanwidget.h"

BooleanWidget::BooleanWidget(QWidget *parent) :
    QWidget(parent)
{
    setMouseTracking(true);

    //Make the background opaque, otherwise the color of the view would be visible
    setAutoFillBackground(true);

    //Create checkbox and make it centered
    checkBox = new QCheckBox(this);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(checkBox, 0, Qt::AlignCenter);
}

bool BooleanWidget::isChecked()
{
    return checkBox->isChecked();
}

void BooleanWidget::setChecked(bool value)
{
    checkBox->setChecked(value);
}

void BooleanWidget::mouseReleaseEvent(QMouseEvent* /*event*/)
{
    emit editingFinished();
}
