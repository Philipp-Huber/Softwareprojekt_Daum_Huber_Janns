#include "booleaneditor.h"

BooleanDelegate::BooleanDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

//void BooleanEditor::paint(QPainter *painter,
//                     const QStyleOptionViewItem &option,
//                     const QModelIndex &index) const
//{
//    //Use standard QItemDelegate function to draw a checkbox
//    drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
//    drawFocus(painter, option, option.rect);
//}

QWidget *BooleanDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    if(index.data().canConvert<bool>())
    {
        QCheckBox* editor = new QCheckBox(parent);
        //connect(editor, &BooleanWidget::editingFinished, this, &BooleanDelegate::commitAndCloseEditor);
        return editor;
    } else {
        return QItemDelegate::createEditor(parent, option, index);
    }
}

//void BooleanDelegate::commitAndCloseEditor()
//{
//    QCheckBox* editor = static_cast<QCheckBox*>(sender());
//    emit commitData(editor);
//    emit closeEditor(editor);
//}

//Initialize editor with data from model
void BooleanDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.data().canConvert<bool>())
    {
        bool value = index.model()->data(index, Qt::EditRole).toBool();
        QCheckBox* widget = static_cast<QCheckBox*>(editor);
        widget->setChecked(value);
    } else {
        return QItemDelegate::setEditorData(editor, index);
    }
}

//Write data to model
void BooleanDelegate::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    QCheckBox* widget = static_cast<QCheckBox*>(editor);
    model->setData(index, widget->isChecked());
}

//Make checkbox fit
void BooleanDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
