#ifndef STAR_H
#define STAR_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QMetaType>
#include <QPointF>
#include <QVector>



class starDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit starDelegate(QObject *parent=0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);


};

#endif // STAR_H
