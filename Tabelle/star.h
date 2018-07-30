#ifndef STAR_H
#define STAR_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QMetaType>
#include <QPointF>
#include <QVector>

/*!
 * \brief The starDelegate class
 *
 * A delegat that paits stars
 */

class starDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit starDelegate(QObject *parent=0);

    /*!
     * \brief Paints the Stars
     *
     * Paint takes the Values 0 (no Satr) and -1 (Star) and Paints stars akordingly
     * Thies integers are for the column sort funktion.
     *
     * \param painter A QPainter
     * \param option The Cell in witch the delegate is aplied
     * \param index the table index ov the cell
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // STAR_H
