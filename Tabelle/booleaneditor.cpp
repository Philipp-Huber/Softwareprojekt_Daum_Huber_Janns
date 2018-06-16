#include "booleaneditor.h"

BooleanDelegate::BooleanDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void BooleanDelegate::paint(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{
    QStyleOptionViewItem viewItemOption(option);
    // Only do this if we are accessing the column with boolean variables.
    if (index.column() == 12 || index.column() == 1) {
      // This basically changes the rectangle in which the check box is drawn.
      const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
      QRect newRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                      QSize(option.decorationSize.width() +
                            5,option.decorationSize.height()),
                      QRect(option.rect.x() + textMargin, option.rect.y(),
                            option.rect.width() -
                            (2 * textMargin), option.rect.height()));
      viewItemOption.rect = newRect;
    }
    // Draw the check box using the new rectangle.
    QStyledItemDelegate::paint(painter, viewItemOption, index);
}

bool BooleanDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
             const QStyleOptionViewItem &option,
             const QModelIndex &index) {
  Q_ASSERT(event);
  Q_ASSERT(model);

  // make sure that the item is checkable
  Qt::ItemFlags flags = model->flags(index);
  if (!(flags & Qt::ItemIsUserCheckable) || !(flags & Qt::ItemIsEnabled)) {
    return false;
  }

  // make sure that we have a check state
  QVariant value = index.data(Qt::CheckStateRole);
  if (!value.isValid()) {
    return false;
  }

  // make sure that we have the right event type
  if (event->type() == QEvent::MouseButtonRelease) {
    const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
    QRect checkRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                      option.decorationSize,
                      QRect(option.rect.x() + (2 * textMargin), option.rect.y(),
                        option.rect.width() - (2 * textMargin),
                        option.rect.height()));
    // We handle the mouse event...
    QMouseEvent *mEvent = (QMouseEvent*) event;
    if (!checkRect.contains(mEvent->pos())) {
      return false;
    }
    // as well as the key press event.
  } else if (event->type() == QEvent::KeyPress) {
    if (static_cast<QKeyEvent*>(event)->key() !=
    Qt::Key_Space&& static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select) {
      return false;
    }
  } else {
    return false;
  }
  // Determine the new check state
  Qt::CheckState state = (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked
              ? Qt::Unchecked : Qt::Checked);
  // And set the new check state by calling the model's setData() function.
  return model->setData(index, state, Qt::CheckStateRole);
}

//QWidget *BooleanDelegate::createEditor(QWidget *parent,
//                                     const QStyleOptionViewItem &option,
//                                     const QModelIndex &index) const
//{
//    if(index.column() == 12)
//    {
//        QCheckBox* editor = new QCheckBox(parent);
//        //connect(editor, &BooleanWidget::editingFinished, this, &BooleanDelegate::commitAndCloseEditor);
//        editor->installEventFilter(const_cast<BooleanDelegate*>(this));
//        return editor;
//    } else {
//        return QStyledItemDelegate::createEditor(parent, option, index);
//    }
//}

//void BooleanDelegate::commitAndCloseEditor()
//{
//    QCheckBox* editor = static_cast<QCheckBox*>(sender());
//    emit commitData(editor);
//    emit closeEditor(editor);
//}

//Initialize editor with data from model
//void BooleanDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    if(index.column() == 12)
//    {
//        bool value = index.model()->data(index, Qt::EditRole).toBool();
//        QCheckBox* widget = static_cast<QCheckBox*>(editor);
//        widget->setChecked(value);
//    } else {
//        return QStyledItemDelegate::setEditorData(editor, index);
//    }
//}

//Write data to model
//void BooleanDelegate::setModelData(QWidget *editor,
//                                 QAbstractItemModel *model,
//                                 const QModelIndex &index) const
//{
//    if(index.column() == 12)
//    {
//        QCheckBox* widget = static_cast<QCheckBox*>(editor);
//        model->setData(index, widget->isChecked());
//    }

//}

//Make checkbox fit
//void BooleanDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    editor->setGeometry(option.rect);
//}
