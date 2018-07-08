#include <QApplication>
#include <QWindow>
#include <QSplitter>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include "booleaneditor.h"
#include "barDelegate.h"
#include "star.h"
#include "mzparser.h"

void insertTableDataIntoModel(QList<QStringList> &list, QStandardItemModel &model);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    QTableView tableViewPeptides;

    //Make instance of models
    QStandardItemModel proteinModel(0);
    QStandardItemModel peptideModel(0);

    //Read test file and fill data structure
    mzTabFile tableData;
    tableData = mzParser::instance().parse("../PRIDE_Exp_Complete_Ac_1643.xml-mztab.txt");

    //Fill models
    insertTableDataIntoModel(tableData.proteins, proteinModel);
    insertTableDataIntoModel(tableData.psm, peptideModel);

    //list of columns with bars
//    const QList<int> barList = {5,6,7,8,9,10,11};
//    const QList<int> peptideBarList = {5,6};

    //Link view to model
    tableView.setModel( &proteinModel );
    tableViewPeptides.setModel(&peptideModel);

//    foreach (int i, barList) {
//        tableView.setItemDelegateForColumn(i, new barDelegate);
//    }

    tableView.setItemDelegateForColumn(proteinModel.columnCount()-1, new BooleanDelegate);
    tableView.setItemDelegateForColumn(1, new starDelegate);
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

//    foreach(int i, peptideBarList){
//        tableViewPeptides.setItemDelegateForColumn(i, new barDelegate);
//    }

    tableViewPeptides.setItemDelegateForColumn(peptideModel.columnCount()-1, new BooleanDelegate);
    tableViewPeptides.setItemDelegateForColumn(1, new BooleanDelegate);
    tableViewPeptides.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //Display
//    tableView.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    tableViewPeptides.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QSplitter *splitter = new QSplitter();
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(&tableView);
    splitter->addWidget(&tableViewPeptides);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    splitter->setWindowTitle("Bars and Checkboxes");
    splitter->show();

    return a.exec();
}

void insertTableDataIntoModel(QList<QStringList> &list, QStandardItemModel &model){
    QStringList HeaderStartPadding = {"", "", "Pl"};
    QStringList HeaderEndPadding = {""};

    if(!list.isEmpty()){
        model.setHorizontalHeaderLabels(HeaderStartPadding + list.first() + HeaderEndPadding);
        list.removeFirst();

        int row = 0;
        while(!list.isEmpty()){
            int column = 0;
            while(!list.first().isEmpty()){
                if(column == 0){
                    QStandardItem *rowNum = new QStandardItem(0);
                    rowNum->setData(row+1, Qt::DisplayRole);
                    rowNum->setEditable(false);
                    model.setItem(row, column, rowNum);
                } else if(column == 1){
                    QStandardItem *star = new QStandardItem(true);
                    star->setEditable(false);
                    star->setCheckable(true);
                    star->setCheckState(Qt::Unchecked);
                    model.setItem(row, column, star);
                } else if(column >= 3){
                    QStandardItem *data = new QStandardItem(0);
                    data->setData(list.first().first(), Qt::DisplayRole);
                    data->setEditable(false);
                    model.setItem(row, column, data);
                    list.first().removeFirst();
                }
                column++;
            }
            QStandardItem *checkbox = new QStandardItem(true);
            checkbox->setEditable(false);
            checkbox->setCheckable(true);
            checkbox->setCheckState(Qt::Unchecked);
            model.setItem(row, column, checkbox);

            list.removeFirst();
            row++;
        }
    }
}
