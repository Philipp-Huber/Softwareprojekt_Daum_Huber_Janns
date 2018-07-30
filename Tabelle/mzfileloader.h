#ifndef MZFILELOADER_H
#define MZFILELOADER_H
#include <QObject>
#include <QTableView>
#include <QHeaderView>
#include <QByteArray>
#include <QDebug>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QItemDelegate>
#include <QFileDialog>
#include "mzparser.h"
#include "barDelegate.h"
#include "star.h"
#include "markdelegate.h"
#include "multbardelegate.h"

/*!
 * \brief The mzFileLoader class
 *
 * Loader that opens file select dialogue, activates parser and fills models. This class acts as a controller and has access to all
 * important objects to be able to efficiently load data.
 */
class mzFileLoader : public QObject
{
    Q_OBJECT

public:
    mzFileLoader(){}

    /*!
     * \brief This function is called from main to make all models available in this class.
     * \param firstModel The protein base model
     * \param secondModel The peptide base model
     */
    void setModels(QStandardItemModel *firstModel, QStandardItemModel *secondModel){
        proteinModel = firstModel;
        peptideModel = secondModel;
    }

    /*!
     * \brief This function is called from main to make all proxies available in this class.
     * \param firstProxy The protein proxy model lowest in the stack
     * \param secondProxy The protein proxy model second lowest in the stack
     * \param thirdProxy The protein proxy model second highest in the stack
     * \param fourthProxy The protein proxy model highest in the stack
     * \param pepProxy The peptide proxy model (it only needs one)
     */
    void setProxies(QSortFilterProxyModel *firstProxy, QSortFilterProxyModel *secondProxy, QSortFilterProxyModel* thirdProxy,
                    QSortFilterProxyModel *fourthProxy, QSortFilterProxyModel *pepProxy){
        proteinProxy = firstProxy;
        proteinProxy2 = secondProxy;
        proteinProxy3 = thirdProxy;
        proteinProxy4 = fourthProxy;
        peptideProxy = pepProxy;
    }

    /*!
     * \brief This function is called from main to make the TableViews available from this class.
     * \param firstTable The protein table
     * \param secondTable The peptide table
     */
    void setTableViews(QTableView *firstTable, QTableView *secondTable){
        proteinTable = firstTable;
        peptideTable = secondTable;
    }

    /*!
     * \brief This function is currently unused. It returns the remaining structure left over after inserting into the model.
     * Maybe someday someone has to look at the leftovers...
     * \return An mzTabFile structure (may be empty or only contain metadata)
     */
    mzTabFile getData(){
        return data;
    }

signals:
    /*!
     * \brief This signal is used to clear the combobox(es) of all entries when loading new files.
     */
    void clearComboBox();

    /*!
     * \brief This signal is used to insert new selectable items into the search combobox(es) when loading new files.
     * \param headers The selectable headers
     */
    void HeaderDataChanged(QStringList headers);

public slots:
    /*!
     * \brief This slot is connected to the "Load File..."-button. This gets everything going. Opens a file dialog to select file to load, then invokes the parser to
     * attempt to parse it. If successful, fills protein and peptide tables with read data.
     */
    void load();

private:
    mzTabFile data;
    QTableView* proteinTable;
    QTableView* peptideTable;
    QSortFilterProxyModel* proteinProxy;
    QSortFilterProxyModel* proteinProxy2;
    QSortFilterProxyModel* proteinProxy3;
    QSortFilterProxyModel* proteinProxy4;
    QSortFilterProxyModel* peptideProxy;
    QStandardItemModel* proteinModel;
    QStandardItemModel* peptideModel;

    /*!
     * \brief This function tears down the proxy depencies during loading of a new table, since QSortFilterProxyModel is awfully inefficient.
     */
    void disconnectProxies();

    /*!
     * \brief This function rebuilds the proxy depencies previously undone by disconnectProxies.
     */
    void reconnectProxies();

    /*!
     * \brief This function takes a list of table rows and inserts its contents into the model.
     * \param list The list of rows to insert
     * \param model The model to insert into
     * \param updateComboBox Should the search selection combobox(es) be updated? True for protein data, false for peptides
     */
    void insertTableDataIntoModel(QList<QStringList> *list, QStandardItemModel *model, bool updateComboBox);

    /*!
     * \brief This function updates the TableViews with delegates and other vital settings. It also reconnects all previously disconnected proxies.
     */
    void updateTableViews();

    /*!
     * \brief This function assigns delegates to the protein table.
     *
     * \param model The protein table to work on
     */
    void updateProteinDelegates(QStandardItemModel *model);

    /*!
     * \brief This function assigns delegate to the peptide table.
     *
     * \param model The peptide table to work on
     */
    void updatePeptideDelegates(QStandardItemModel *model);
};

#endif // MZFILELOADER_H
