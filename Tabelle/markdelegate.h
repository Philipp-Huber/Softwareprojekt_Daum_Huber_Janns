#ifndef MARKDELEGATE_H
#define MARKDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QtMath>

/*!
 * \brief The markDelegate class
 *
 * sets a marker using a logarithmik function
 */
class markDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    markDelegate(QWidget *parent = 0 ) : QStyledItemDelegate(parent){}



    /*!
     * \brief Paints the marker
     *
     * Paint takes a value between 0 and 2¹⁴ and agusts the bars lenght akordingly
     *
     * \param painter A QPainter
     * \param option The Cell in witch the delegate is aplied
     * \param index the table index ov the cell
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

#endif // MARKDELEGATE_H
