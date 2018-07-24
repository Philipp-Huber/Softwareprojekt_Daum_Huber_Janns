#include "mzfileloader.h"

//public slot, gets called by clicking on the "Load File..."-button
void mzFileLoader::load(){
    //Opens file selection dialog, returns nullpointer if closed without selecting anything
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("Open mzTab File"), "", tr("mzTab (*.mz *.mztab);;Text Files (*.txt)"));

    if(fileName.isNull()){
        return;
    } else {
        //We got a file name, so let the parser do its magic
        data = mzParser::instance().parse(fileName.toStdString());
        if(data.isValid){
            insertTableDataIntoModel(&data.proteins, proteinModel, true);
            //Important: If there is no direct peptide data in the file, use PSM instead
            peptideTable->setModel(peptideModel);
            if(!data.peptides.empty()){ 
                insertTableDataIntoModel(&data.peptides, peptideModel, false);
            } else {
                insertTableDataIntoModel(&data.psm, peptideModel, false);
            }
            //Important: Delegates get set here!
            updateTableViews();
        } else {
            return;
        }
    }
}

void mzFileLoader::catchInvalidSortIndicator(int logicalIndex){
    if(logicalIndex == 1){
        if(QObject::sender() != NULL){
            qobject_cast<QHeaderView*>(QObject::sender())->setSortIndicator(0, Qt::SortOrder::AscendingOrder);
        }
    }
}

//Params:
//list: pointer to one of the lists of lists contained in an mzFileTab struct, will be deleted entry by entry
//model: pointer to model to be filled; filled entry by entry with data from list
//updateComboBox: does the search column selection box need to update its items with new column headers?
void mzFileLoader::insertTableDataIntoModel(QList<QStringList> *list, QStandardItemModel *model, bool updateComboBox = true){
    //Columns we know every table starts and ends with, data read from files goes inbetween
    QStringList HeaderStartPadding = {"Row #", "Star", "Pl"};
    QStringList HeaderEndPadding = {"Checked"};

    //If we have already loaded a file, we need to unload first, otherwise old data survives if the new table is smaller
    model->removeRows(0, model->rowCount());

    if(!list->isEmpty()){
        //If we had a previous file loaded with more columns than the new one, the model will retain that count
        model->setColumnCount(list->first().count() + HeaderStartPadding.count() + HeaderEndPadding.count());
        //Since every QStringList in list represents one row in order from top to bottom,
        //we know the headers are the first list in the outer list
        model->setHorizontalHeaderLabels(HeaderStartPadding + list->first() + HeaderEndPadding);
        if(updateComboBox){
            //Clear all items from search selection box and fill it with the new headers
            emit clearComboBox();
            emit HeaderDataChanged(HeaderStartPadding + list->first() + HeaderEndPadding);
        }
        //Headers are inserted, so we can remove them. After that, the first list is the first row of items
        list->removeFirst();

        //Each item in the outer list is a row, each item in the inner list is an item for each column
        int row = 0;
        while(!list->isEmpty()){
            int column = 0;
            while(!list->first().isEmpty()){
                //Extra items for columns 0 to 2, since they're not in the loaded file
                if(column == 0){
                    QStandardItem *rowNum = new QStandardItem(0);
                    rowNum->setData(row+1, Qt::DisplayRole);
                    rowNum->setEditable(false);
                    model->setItem(row, column, rowNum);
                } else if(column == 1){
                    QStandardItem *star = new QStandardItem(true);
                    star->setEditable(false);
                    star->setCheckable(true);
                    star->setCheckState(Qt::Unchecked);
                    model->setItem(row, column, star);
                } else if(column >= 3){
                    //Create item from read file
                    QStandardItem *data = new QStandardItem(0);
                    data->setData(list->first().first(), Qt::DisplayRole);
                    data->setEditable(false);
                    model->setItem(row, column, data);
                    //Column done, remove it, so the next column becomes first (that's the magic)
                    list->first().removeFirst();
                }
                column++;
            }
            //Last column item is also not in the file, so it gets set here, after everything else
            QStandardItem *checkbox = new QStandardItem(true);
            checkbox->setEditable(false);
            checkbox->setCheckable(true);
            checkbox->setCheckState(Qt::Unchecked);
            model->setItem(row, column, checkbox);

            //Row done, remove it so the next row becomes first
            list->removeFirst();
            row++;
        }
    }
}

//TODO: Figure out which Delegates should go into each column that we read from file
void mzFileLoader::updateTableViews(){
    //list of columns with bars
//    const QList<int> barList = {5,6,7,8,9,10,11};
//    const QList<int> peptideBarList = {5,6};

//    foreach (int i, barList) {
//        tableView.setItemDelegateForColumn(i, new barDelegate);
//    }
    //allow sorting by column
//    proteinTable->setSortingEnabled(true);

    proteinTable->horizontalHeader()->resizeSection(1,40);
    proteinTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);

    proteinTable->setItemDelegate(new QItemDelegate); //overwrite all formerly set delegates (to be sure)
    proteinTable->setItemDelegateForColumn(proteinModel->columnCount()-1, new BooleanDelegate);
    proteinTable->setItemDelegateForColumn(1, new starDelegate);

//    foreach(int i, peptideBarList){
//        tableViewPeptides.setItemDelegateForColumn(i, new barDelegate);
//    }
    peptideTable->setModel(peptideProxy);
    peptideTable->setSortingEnabled(true);
    peptideTable->horizontalHeader()->resizeSection(1,40);
    peptideTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);

    peptideTable->setItemDelegate(new QItemDelegate);
    peptideTable->setItemDelegateForColumn(peptideModel->columnCount()-1, new BooleanDelegate);
    peptideTable->setItemDelegateForColumn(1, new starDelegate);
}
