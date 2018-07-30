#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

/*!
 * \brief The barDelegate class
 *
 * The barDelegate class offers a way of displaying percentages (numbers betwen 0 and 1)
 *
 */

class barDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    barDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    /*!
     * \brief Paints the Bar
     *
     * Paint takes a value between 0 and 1 and adjusts the bar's lenght accordingly
     *
     * \param painter A QPainter
     * \param option The cell to which the delegate is applied
     * \param index The table index of the cell
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

};



#endif // BARDELEGATE_H
