#include "booleaneditor.h"

BooleanEditor::BooleanEditor(QObject *parent) :
    QItemDelegate(parent)
{
}

void BooleanEditor::paint(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{
    //Use standard QItemDelegate function to draw a checkbox
    drawCheck(painter, option, option.rect, index.data().toBool() ? Qt::Checked : Qt::Unchecked);
    drawFocus(painter, option, option.rect);
}

QWidget *BooleanEditor::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    BooleanWidget* editor = new BooleanWidget(parent);
    connect(editor, &BooleanWidget::editingFinished, this, &BooleanEditor::commitAndCloseEditor);
    return editor;
}

void BooleanEditor::commitAndCloseEditor()
{
    BooleanWidget* editor = qobject_cast<BooleanWidget*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

//Initialize editor with data from model
void BooleanEditor::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    BooleanWidget* widget = qobject_cast<BooleanWidget*>(editor);
    widget->setChecked(index.data().toBool());
}

//Write data to model
void BooleanEditor::setModelData(QWidget *editor,
                                 QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    BooleanWidget * widget = qobject_cast<BooleanWidget*>(editor);
    model->setData(index, widget->isChecked());
}
