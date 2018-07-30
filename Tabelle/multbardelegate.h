#ifndef MULTBARDELEGATE_H
#define MULTBARDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QtMath>
/*!
 * \brief The multBarDelegate class
 *
 * makes Multikulerd bars
 */
class multBarDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    multBarDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    /*!
     * \brief Paints the Bar
     *
     * Paint takes a value between 0 and 2⁸ and agusts the bars lenght akordingly
     * the bar colors are in acordence with thier length
     *
     * \param painter A QPainter
     * \param option The Cell in witch the delegate is aplied
     * \param index the table index ov the cell
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

 };

#endif // MULTBARDELEGATE_H
