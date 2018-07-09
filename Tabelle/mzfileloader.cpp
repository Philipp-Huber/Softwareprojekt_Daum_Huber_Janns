#include "mzfileloader.h"

void mzFileLoader::load(){
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("Open mzTab File"), "", tr("mzTab (*.mz *.mztab);;Text Files (*.txt)"));

    if(fileName.isNull()){
        return;
    } else {
        data = mzParser::instance().parse(fileName.toStdString());
        if(data.isValid){
            insertTableDataIntoModel(&data.proteins, proteinModel, true);
            if(!data.peptides.empty()){
                insertTableDataIntoModel(&data.peptides, peptideModel, false);
            } else {
                insertTableDataIntoModel(&data.psm, peptideModel, false);
            }
            updateTableViews();
        } else {
            return;
        }
    }
}

void mzFileLoader::insertTableDataIntoModel(QList<QStringList> *list, QStandardItemModel *model, bool updateComboBox = true){
    QStringList HeaderStartPadding = {"Row #", "Star", "Pl"};
    QStringList HeaderEndPadding = {"Checked"};

    model->removeRows(0, model->rowCount());

    if(!list->isEmpty()){
        model->setColumnCount(list->first().count() + HeaderStartPadding.count() + HeaderEndPadding.count());
        model->setHorizontalHeaderLabels(HeaderStartPadding + list->first() + HeaderEndPadding);
        if(updateComboBox){
            emit clearComboBox();
            emit HeaderDataChanged(HeaderStartPadding + list->first() + HeaderEndPadding);
        }
        list->removeFirst();

        int row = 0;
        while(!list->isEmpty()){
            int column = 0;
            while(!list->first().isEmpty()){
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
                    QStandardItem *data = new QStandardItem(0);
                    data->setData(list->first().first(), Qt::DisplayRole);
                    data->setEditable(false);
                    model->setItem(row, column, data);
                    list->first().removeFirst();
                }
                column++;
            }
            QStandardItem *checkbox = new QStandardItem(true);
            checkbox->setEditable(false);
            checkbox->setCheckable(true);
            checkbox->setCheckState(Qt::Unchecked);
            model->setItem(row, column, checkbox);

            list->removeFirst();
            row++;
        }
    }
}

void mzFileLoader::updateTableViews(){
    //list of columns with bars
//    const QList<int> barList = {5,6,7,8,9,10,11};
//    const QList<int> peptideBarList = {5,6};

//    foreach (int i, barList) {
//        tableView.setItemDelegateForColumn(i, new barDelegate);
//    }

    proteinTable->setItemDelegate(new QItemDelegate); //overwrite all formerly set delegates
    proteinTable->setItemDelegateForColumn(proteinModel->columnCount()-1, new BooleanDelegate);
    proteinTable->setItemDelegateForColumn(1, new starDelegate);

//    foreach(int i, peptideBarList){
//        tableViewPeptides.setItemDelegateForColumn(i, new barDelegate);
//    }

    peptideTable->setItemDelegate(new QItemDelegate);
    peptideTable->setItemDelegateForColumn(peptideModel->columnCount()-1, new BooleanDelegate);
    peptideTable->setItemDelegateForColumn(1, new starDelegate);
}
