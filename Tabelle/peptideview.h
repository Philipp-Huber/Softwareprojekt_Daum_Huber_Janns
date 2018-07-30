#ifndef PEPTIDEVIEW_H
#define PEPTIDEVIEW_H

#include <QTableView>
#include <QObject>

/*!
 * \brief The PeptideView class
 *
 * The PeptideView class offers a customized version of the QTableView class. In addition to the QTableView functions
 * it offers a slot which can hide and show rows depending on given entries.
 */
class PeptideView : public QTableView
{
    Q_OBJECT
protected:
     bool eventFilter(QObject*, QEvent*) override;
public:
    PeptideView();



signals:
     /*!
      * \brief This signal is a parameter free notification
      */
     void updateStar();



public slots:
   /*!
     * \brief This function hides and shows rows according to it's input
     *
     * toBeDisplayed receives a List of accesion codes as QStrings. If the model contains a column with header "accession"
     * the function will set all rows as shown, for which the entries in the accession column are contained in the input, and set all
     * columns as hidden for which the entries aren't.
     * If the model does not contain such a column, the function will return without doing anything.
     * This function can be connected as a Slot
     *
     * @param QList<QString> contains a List of accession codes as QStrings
     */
    void toBeDisplayed(QList<QString>);

    /*!
     * \brief This fuction marks Stars
     *
     * updateEventStar unmarkes all stars
     * Checks witch Rows in the Peptide Table are selected
     * and then marks stars in selected rows.
     *
     */

    void updateEventStar();

    /*!
     * \brief Clears all stars in the Peptide Table
     */
    void clearPepStar();

};

#endif // PEPTIDEVIEW_H
