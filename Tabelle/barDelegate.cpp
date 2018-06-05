#include <QApplication>
#include <QtWidgets/QTableView>
#include "barDelegate.h"


void barDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

        if (index.data().canConvert<int>()) {
            barCreator Bar = barCreator(index.data().toInt());

            if (option.state & QStyle::State_Selected)
                painter->fillRect(option.rect, option.palette.highlight());

            Bar.paint(painter, option.rect, option.palette,
                             barCreator::ReadOnly);
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }

}
//inherited sizeHint() should work fine
/*
QSize barDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (index.data().canConvert<barCreator>()) {
        barCreator Bar = qvariant_cast<barCreator>(index.data());
        return Bar.sizeHint();
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}
*/


// No editor necessary as bars will only be visualisation
/*
QWidget *barDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const

{
    if (index.data().canConvert<barCreator>()) {
        barEditor *editor = new barEditor(parent);
        connect(editor, &barEditor::editingFinished,
                this, &barDelegate::commitAndCloseEditor);
        return editor;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void barDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    if (index.data().canConvert<barCreator>()) {
        barEditor *BarEdit = qobject_cast<barEditor *>(editor);
        BarEdit->barRating();
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void barDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    if (index.data().canConvert<barCreator>()) {
        barEditor *barEdit = qobject_cast<barEditor *>(editor);
        model->setData(index, QVariant::fromValue(barEdit->BarCreator()));
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void barDelegate::commitAndCloseEditor()
{
    barEditor *editor = qobject_cast<barEditor *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
*/
