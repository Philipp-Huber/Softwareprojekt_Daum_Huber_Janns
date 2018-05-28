#ifndef BOOLEANWIDGET_H
#define BOOLEANWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QHBoxLayout>

class BooleanWidget : public QWidget
{
    Q_OBJECT
    QCheckBox* checkBox;

public:
    explicit BooleanWidget(QWidget *parent = 0);
    bool isChecked();
    void setChecked(bool value);

signals:
    void editingFinished();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;

public slots:

};

#endif // BOOLEANWIDGET_H
