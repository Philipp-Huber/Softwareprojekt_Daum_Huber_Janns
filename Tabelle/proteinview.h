#ifndef PROTEINVIEW_H
#define PROTEINVIEW_H

#include<QTableView>
#include<QObject>

/*!
 * \brief The ProteinView class
 *
 * The ProteinView class offers a customized version of the QTableView class. In addition to the QTableView functions
 * it integrates mouse release events over the entire viewing area, and extra signals to connect the aforementioned events,
 * emit a list of selected AccessionNumbers, aswell as a custom slot to trigger the generation and emission of said list.
 */
class ProteinView : public QTableView
{
    Q_OBJECT

public:
    ProteinView();

protected:
    /*!
     * \brief This function emits an empty Signal when called with QEvent::MouseButtonRelease
     * \return Returns true if Signal was emitted, else returns false
     */
    bool eventFilter(QObject*, QEvent*) override;

signals:
    /*!
     * \brief This signal is a parameter free notification
     */
    void update();
    /*!
     * \brief This signal transmits a list of Strings
     */
    void activeAccessions(QList<QString>);

public slots:
    /*!
     * \brief This function generates and emits a list of selected AccessionCode Entries
     *
     * updateEvent produces and emits a list of QStrings of all model entries in the first column with header "accession", if the column exists,
     * for which the entire row is selected. The List will contain all entries in said column, should no or all rows be selected.
     * The function can be connected as a Slot.
     *
     * Annotation: The function is intended to be used with the Viewers selectionBehavior set to selectRows
     */
    void updateEvent();

};

#endif // PROTEINVIEW_H
