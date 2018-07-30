#ifndef BARDELEGATE_H
#define BARDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

/*!
 * \brief The barDelegate class
 *
 * The barDelegate class offer a way of
 * displaing percentiges (Numers betwen 0 and 1)
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
     * Paint takes a value between 0 and 1 and agusts the bars lenght akordingly
     *
     * \param painter A QPainter
     * \param option The Cell in witch the delegate is aplied
     * \param index the table index ov the cell
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

};



#endif // BARDELEGATE_H
