#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>


class barDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    barDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
/*
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
*/
private slots:
//    void commitAndCloseEditor();

};



#endif // BARDELEGATE_H
