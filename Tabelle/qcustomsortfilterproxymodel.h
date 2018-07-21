#ifndef QCUSTOMSORTFILTERPROXYMODEL_H
#define QCUSTOMSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

/*!
 * \brief The QCustomSortFilterProxyModel class
 *
 * The QCustomSortFilterProxyModel class offers a customized version of the QSortFilterProxyModel class. In addition to the inherited functions
 * it provides a Slot to externally change the filtered column, aswell as a Slot that forwards a signal containing a new String by which the model is filtered, aswell as
 * emits an empty signal, denoting that the model has changed.
 */
class QCustomSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    /*!
     * \brief QCustomSortFilterProxyModel creates an instance of the class
     * \param *parent points to a QObject that is to be set as parent object for the created instance
     *
     * This constructor creates an instance of the class and initializes the connection from the customSetFilterFixedString Slot to
     * the inherited setFilterFixedString Slot.
     */
    explicit QCustomSortFilterProxyModel(QObject *parent = 0);


signals:
    /*!
     * \brief This signal notifies it's connected slots that the model was updated
     */
    void modelUpdated();
    /*!
     * \brief this signal forwards the new QString by which the model is filtered
     */
    void updateFilter(QString);

public slots:
    /*!
     * \brief This function updates the column by which values the model is filtered
     * \param col must strictly contain an integer: -1 < col < number of columns in the model
     *
     * This function allows external signals to set the column by which values the model is filtered.
     * It must in all instances be called by an acceptable column index, otherwise it will throw an
     * OutOfBounds exception.
     * This function can be connected as a Slot
     */
    void changeFilterKeyColumn(int col){
        this->setFilterKeyColumn(col);
    }
    /*!
     * \brief This function receives a Filter String and forwards it appropriately
     *
     * This function receives incoming Signals containing a FilterString which it forwards to the inherited
     * function QSortFilterProxyModel::setFilterFixedString(QString) (see constructor documentation), to set the new String by which the model
     * is filtered. It then emits modelUpdated(), indicating that the model may have changed.
     */
    void customSetFilterFixedString(QString);
};

#endif // QCUSTOMSORTFILTERPROXYMODEL_H
