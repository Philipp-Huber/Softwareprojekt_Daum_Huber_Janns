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
 * A delegate that paints stars
 */

class starDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit starDelegate(QObject *parent=0);

    /*!
     * \brief Paints the Stars
     *
     * Paint takes the values 0 (no Star) and -1 (Star) and paints stars accordingly
     * These integers are for the column sort function.
     *
     * \param painter A QPainter
     * \param option The cell to which the delegate is applied
     * \param index The table index of the cell
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // STAR_H
