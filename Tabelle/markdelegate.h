#ifndef MARKDELEGATE_H
#define MARKDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QtMath>

/*!
 * \brief The markDelegate class
 *
 * Sets a marker using a logarithmic function
 */
class markDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    markDelegate(QWidget *parent = 0 ) : QStyledItemDelegate(parent){}



    /*!
     * \brief Paints the marker
     *
     * Paint takes a value between 0 and 2¹⁴ and agusts the bars length accordingly
     *
     * \param painter A QPainter
     * \param option The cell in witch the delegate is applied
     * \param index The table index of the cell
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // MARKDELEGATE_H
