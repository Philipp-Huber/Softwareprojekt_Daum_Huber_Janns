#ifndef BOOLEANEDITOR_H
#define BOOLEANEDITOR_H

#include <QItemDelegate>
#include <QCheckBox>

class BooleanDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit BooleanDelegate(QObject *parent = 0);
    //void paint(QPainter *painter, const QStyleOptionViewItem &option,
    //           const QModelIndex &index) const override;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:
    //void commitAndCloseEditor();

};

#endif // BOOLEANEDITOR_H
