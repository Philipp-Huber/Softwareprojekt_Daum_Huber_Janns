#ifndef MZFILELOADER_H
#define MZFILELOADER_H
#include <QObject>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QItemDelegate>
#include <QFileDialog>
#include "mzparser.h"
#include "booleaneditor.h"
#include "barDelegate.h"
#include "star.h"
#include "markdelegate.h"

//Loader that opens file select dialogue, activates parser and fills models
class mzFileLoader : public QObject
{
    Q_OBJECT

public:
    mzFileLoader(){}

    void setModels(QStandardItemModel *firstModel, QStandardItemModel *secondModel){
        proteinModel = firstModel;
        peptideModel = secondModel;
    }
    void setProxy(QSortFilterProxyModel *firstproxy){
        peptideProxy = firstproxy;
    }

    void setTableViews(QTableView *firstTable, QTableView *secondTable){
        proteinTable = firstTable;
        peptideTable = secondTable;
    }

    mzTabFile getData(){
        return data;
    }

signals:
    void clearComboBox();
    void HeaderDataChanged(QStringList headers);

public slots:
    void load();

    void catchInvalidSortIndicator(int logicalIndex);

private:
    mzTabFile data;
    QTableView* proteinTable;
    QTableView* peptideTable;
    QSortFilterProxyModel* peptideProxy;
    QStandardItemModel* proteinModel;
    QStandardItemModel* peptideModel;


    void insertTableDataIntoModel(QList<QStringList> *list, QStandardItemModel *model, bool updateComboBox);
    void updateTableViews();
    void updateProteinDelegates(QStandardItemModel *model);
};

#endif // MZFILELOADER_H
