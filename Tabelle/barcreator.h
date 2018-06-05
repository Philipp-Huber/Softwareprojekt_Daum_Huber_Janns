#ifndef BARCREATOR_H
#define BARCREATOR_H

#include <QMetaType>
#include <QPointF>
#include <QVector>

class barCreator
{
public:

    enum EditMode { Editable, ReadOnly };

    explicit barCreator();
    explicit barCreator(int);


    void paint(QPainter *painter, const QRect &rect,
               const QPalette &palette, EditMode mode) const;


private:
    QPolygonF conBar;
};

Q_DECLARE_METATYPE(barCreator)
#endif // BARCREATOR_H
