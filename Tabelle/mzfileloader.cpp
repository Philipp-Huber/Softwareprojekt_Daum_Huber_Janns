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
            //Performance improvement: No proxy models linked to table view while filling
            proteinTable->setModel(proteinModel);
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
   /* if(logicalIndex == 1){
        if(QObject::sender() != NULL){
            qobject_cast<QHeaderView*>(QObject::sender())->setSortIndicator(0, Qt::SortOrder::AscendingOrder);
        }
    }*/
}

//Params:
//list: pointer to one of the lists of lists contained in an mzFileTab struct, will be deleted entry by entry
//model: pointer to model to be filled; filled entry by entry with data from list
//updateComboBox: does the search column selection box need to update its items with new column headers?
void mzFileLoader::insertTableDataIntoModel(QList<QStringList> *list, QStandardItemModel *model, bool updateComboBox = true){
    //Columns we know every table starts and ends with, data read from files goes inbetween
    const QStringList HeaderStartPadding = {"Row #", "Star", "Pl"};
    const QStringList ComboBoxStartPadding = {"Row #", "Pl"};

    if(!list->isEmpty()){
        //If we had a previous file loaded with more rows or columns than the new one, the model would retain that count
        model->setColumnCount(list->first().count() + HeaderStartPadding.count());
        model->setRowCount(list->count()-1);
        //Since every QStringList in list represents one row in order from top to bottom,
        //we know the headers are the first list in the outer list
        model->setHorizontalHeaderLabels(HeaderStartPadding + list->first());
        if(updateComboBox){
            //Clear all items from search selection box and fill it with the new headers
            emit clearComboBox();
            emit HeaderDataChanged(ComboBoxStartPadding + list->first());
        }
        //Headers are inserted, so we can remove them. After that, the first list is the first row of items
        list->removeFirst();

        //Each item in the outer list is a row, each item in the inner list is an item for each column
        int row = 0;
        while(!list->isEmpty()){
            int column = 0;
            while(!list->first().isEmpty()){
                //Extra items for columns 0 to 2, since they're not in the loaded file
                QString header = model->headerData(column,Qt::Horizontal).toString();
              //  qDebug() << header;

                if(column == 0){
                    QStandardItem *rowNum = new QStandardItem(0);
                    rowNum->setData(row+1, Qt::DisplayRole);
                    rowNum->setEditable(false);
                    model->setItem(row, column, rowNum);
                } else if(column == 1){
                    QStandardItem *star = new QStandardItem(true);
                   star->setEditable(false);
                   star->setData(0, Qt::DisplayRole);
                   model->setItem(row, column, star);

                } else if(header=="protein_abundance_assay[1]" || header=="protein_abundance_assay[2]" ||
                          header=="protein_abundance_assay[3]" || header=="protein_abundance_assay[4]" ){
                    QStandardItem *data = new QStandardItem(0);
                    QVariant value = QVariant::fromValue(list->first().first());
                    if(value.convert(QMetaType::Double)){
                        data->setData(value, Qt::DisplayRole);
                    } else {
                        data->setData(list->first().first(), Qt::DisplayRole);
                    }

                    data->setEditable(true);
                    model->setItem(row, column, data);
                    list->first().removeFirst();



                }

                else if(header=="best_search_engine_score[1]" || header=="search_engine_score[1]" ){
                                   QStandardItem *data = new QStandardItem(0);
                                   QVariant value = QVariant::fromValue(list->first().first());
                                   if(value.convert(QMetaType::Double)){
                                       data->setData(value, Qt::DisplayRole);
                                   } else {
                                       data->setData(list->first().first(), Qt::DisplayRole);
                                   }

                                   data->setEditable(true);
                                   model->setItem(row, column, data);
                                   list->first().removeFirst();
                               }
                else if(column >= 3){
                    //Create item from read file
                    QStandardItem *data = new QStandardItem(0);
                    QVariant value = QVariant::fromValue(list->first().first());
                    if(value.convert(QMetaType::Double)){
                        data->setData(value, Qt::DisplayRole);
                    } else {
                        data->setData(list->first().first(), Qt::DisplayRole);
                    }
                    data->setEditable(true);
                    model->setItem(row, column, data);
                    //Column done, remove it, so the next column becomes first (that's the magic)
                    list->first().removeFirst();
                }
                column++;
            }
            //Row done, remove it so the next row becomes first
            list->removeFirst();
            row++;
        }
    }
}

//TODO: Figure out which Delegates should go into each column that we read from file
void mzFileLoader::updateTableViews(){


    proteinTable->setModel(proteinProxy);
    proteinTable->setSortingEnabled(true);
    proteinTable->horizontalHeader()->resizeSection(1,40);
    proteinTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);

    proteinTable->setItemDelegate(new QItemDelegate); //overwrite all formerly set delegates (to be sure)
    proteinTable->setItemDelegateForColumn(1, new starDelegate);
//  Ordnet  Spalten Delegates zu
    updateProteinDelegates(proteinModel);

//    foreach(int i, peptideBarList){
//        tableViewPeptides.setItemDelegateForColumn(i, new barDelegate);
//    }
    peptideTable->setModel(peptideProxy);
    peptideTable->setSortingEnabled(true);
    peptideTable->horizontalHeader()->resizeSection(1,40);
    peptideTable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);

    peptideTable->setItemDelegate(new QItemDelegate);
    peptideTable->setItemDelegateForColumn(1, new starDelegate);
    updatePtideDelegates(peptideModel);
}

void mzFileLoader::updateProteinDelegates(QStandardItemModel *model){
    for (int column=0; column<model->columnCount(); column++){
        QString header = model->headerData(column,Qt::Horizontal).toString();
        if (header=="protein_abundance_assay[1]" || header=="protein_abundance_assay[2]" ||
                header=="protein_abundance_assay[3]" || header=="protein_abundance_assay[4]"){
            proteinTable->setItemDelegateForColumn(column, new barDelegate);
        }
        if (header=="best_search_engine_score[1]"){
            proteinTable->setItemDelegateForColumn(column, new markDelegate);
        }
    }

}

void mzFileLoader::updatePtideDelegates(QStandardItemModel *model)
{
    for (int column=0; column<model->columnCount(); column++){
        QString header = model->headerData(column,Qt::Horizontal).toString();
        if (header=="protein_abundance_assay[1]" || header=="protein_abundance_assay[2]" ||
                header=="protein_abundance_assay[3]" || header=="protein_abundance_assay[4]"){
           peptideTable->setItemDelegateForColumn(column, new barDelegate);
        }
        if (header=="best_search_engine_score[1]"){
            peptideTable->setItemDelegateForColumn(column, new markDelegate);
        }
        if (header=="search_engine_score[1]"){
            peptideTable->setItemDelegateForColumn(column, new multBarDelegate);
        }
    }
}





