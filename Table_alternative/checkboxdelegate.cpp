#include "checkboxdelegate.h"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

// TableView need to create an Editor
// Create Editor when we construct CheckBoxDelegate
// and return the Editor
QWidget* CheckBoxDelegate::createEditor(QWidget *parent,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{

    QCheckBox *editor = new QCheckBox(parent);
    //editor->setMinimum(0);
    //editor->setMaximum(100);
    return editor;
}

// Then, we set the Editor
// Gets the data from Model and feeds the data to Editor
void CheckBoxDelegate::setEditorData(QWidget *editor,
                               const QModelIndex &index) const
{
    // Get the value via index of the Model
    int value = index.model()->data(index, Qt::EditRole).toBool();

    // Put the value into the CheckBox
    QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
    checkbox->setChecked(value);
}

// When we modify data, this model reflect the change
void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                              const QModelIndex &index) const
{
    QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
    //checkbox->interpretText();
    bool value = checkbox->isChecked();
    model->setData(index, value, Qt::EditRole);
}

// Give the SpinBox the info on size and location
void CheckBoxDelegate::updateEditorGeometry(QWidget *editor,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
