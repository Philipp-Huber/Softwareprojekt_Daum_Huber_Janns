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
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
//                          const QModelIndex &index) const override;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
//    void setModelData(QWidget *editor, QAbstractItemModel *model,
//                      const QModelIndex &index) const override;
//    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:
    //void commitAndCloseEditor();

};

#endif // BOOLEANEDITOR_H
