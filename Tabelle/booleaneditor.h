#ifndef BOOLEANEDITOR_H
#define BOOLEANEDITOR_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QMouseEvent>
#include <QCheckBox>

class BooleanDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BooleanDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);


};

#endif // BOOLEANEDITOR_H
