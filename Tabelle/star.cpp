#include "star.h"
#include <cmath>

starDelegate::starDelegate (QObject *parent):
    QStyledItemDelegate(parent)
{
}


void starDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        QVariant value = index.data(Qt::CheckStateRole);
        if(value==0){
            //Create rect to paint
            QRect r = option.rect;
            QPolygonF s;
            s << QPointF(30.0, 15);
                for (int i = 1; i < 5; ++i){
                  s << QPointF(15 + 0.5 * (std::cos((-0.2+0.4 * i) * 3.14))*10,
                                         15 + 0.5 *( std::sin((-0.2+0.4 * i) * 3.14))*10);
                  s << QPointF(15 + std::cos(0.4 * i * 3.14)*15,
                                           15 +  std::sin(0.4 * i * 3.14)*15);

                 }
                s << QPointF(15 + 0.5 * (std::cos((-0.2+0.4 * 5) * 3.14))*10,
                                     15 + 0.5 *( std::sin((-0.2+0.4 * 5) * 3.14))*10);

            //Adjust base rect so it isn't flush with the cell borders
                //r.setWidth(r.width() * 0.9);
                //r.moveLeft(option.rect.left() + 0.5 * (option.rect.width() - r.width())); //Move right -> add
                //r.setHeight(r.height() * 0.5);
                //r.moveBottom(option.rect.bottom() - 0.5 * (option.rect.height() - r.height())); // Move up -> subtract

            //Set final width
            //r.setWidth(r.width());
            //Paint the bars
            painter->save();

            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->translate(r.x(),r.y()+6);
            painter->rotate(-18);
            painter->setBrush(QBrush(Qt::white));
            painter->drawPolygon(s,Qt::WindingFill);

            painter->restore();
        } else if (value==2){
            //Create rect to paint
            QRect r = option.rect;
            QPolygonF s;
            s << QPointF(30.0, 15);
                for (int i = 1; i < 5; ++i){
                  s << QPointF(15 + 0.5 * (std::cos((-0.2+0.4 * i) * 3.14))*10,
                                         15 + 0.5 *( std::sin((-0.2+0.4 * i) * 3.14))*10);
                  s << QPointF(15 + std::cos(0.4 * i * 3.14)*15,
                                           15 +  std::sin(0.4 * i * 3.14)*15);

                 }
                s << QPointF(15 + 0.5 * (std::cos((-0.2+0.4 * 5) * 3.14))*10,
                                     15 + 0.5 *( std::sin((-0.2+0.4 * 5) * 3.14))*10);






            //Paint the bars
            painter->save();

            painter->setRenderHint(QPainter::Antialiasing, true);
            painter->translate(r.x(),r.y()+6);
            painter->setBrush(QBrush(Qt::black));
            painter->rotate(-18);
            painter->drawPolygon(s,Qt::WindingFill);

            painter->restore();
        }else{
           QStyledItemDelegate::paint(painter, option, index);
        }


}



/*bool starDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
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

  emit starKlicked(index.row());

  // Determine the new check state
  Qt::CheckState state = (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked
              ? Qt::Unchecked : Qt::Checked);
  // And set the new check state by calling the model's setData() function.
  return model->setData(index, state, Qt::CheckStateRole);
}



*/
















