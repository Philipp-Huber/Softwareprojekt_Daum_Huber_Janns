#ifndef MULTBARDELEGATE_H
#define MULTBARDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QtMath>
/*!
 * \brief The multBarDelegate class
 *
 * Makes multicolored bars
 */
class multBarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    multBarDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    /*!
     * \brief Paints the Bar
     *
     * Paint takes a value between 0 and 2⁸ and adjusts the bar's length accordingly
     * the bar colors are in accordance with their length
     *
     * \param painter A QPainter
     * \param option The cell to which the delegate is applied
     * \param index The table index of the cell
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

 };

#endif // MULTBARDELEGATE_H
