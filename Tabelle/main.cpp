#include <QApplication>
#include <QWindow>
#include <QSplitter>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include "booleaneditor.h"
#include "barDelegate.h"
#include "star.h"
#include "mzparser.h"
#include "peptideview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    tableView.setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView.setSelectionMode(QAbstractItemView::MultiSelection);


    PeptideView tableViewPeptides;

    //Make instance of models
    QStandardItemModel myModel(0);
    QStandardItemModel peptideModel(0);

    QObject::connect(&tableView, SIGNAL(clicked(QModelIndex)),
            &tableViewPeptides, SLOT(toBeDisplayed(QModelIndex)));

    //Read test file and fill data structure
    mzTabFile tableData;
    tableData = mzParser::instance().parse("../PRIDE_Exp_Complete_Ac_1643.xml-mztab.txt");

    QStringList HeaderPadding = {"", "", "Pl"};

    if(!tableData.proteins.isEmpty()){
        myModel.setHorizontalHeaderLabels(HeaderPadding + tableData.proteins.first() + QStringList(""));
        tableData.proteins.removeFirst();

        int row = 0;
        while(!tableData.proteins.isEmpty()){
            int column = 0;
            while(!tableData.proteins.first().isEmpty()){
                if(column == 0){
                    QStandardItem *rowNum = new QStandardItem(0);
                    rowNum->setData(row+1, Qt::DisplayRole);
                    rowNum->setEditable(false);
                    myModel.setItem(row, column, rowNum);
                } else if(column == 1){
                    QStandardItem *star = new QStandardItem(true);
                    star->setEditable(false);
                    star->setCheckable(true);
                    star->setCheckState(Qt::Unchecked);
                    myModel.setItem(row, column, star);
                } else if(column >= 3){
                    QStandardItem *data = new QStandardItem(0);
                    data->setData(tableData.proteins.first().first(), Qt::DisplayRole);
                    data->setEditable(false);
                    myModel.setItem(row, column, data);
                    tableData.proteins.first().removeFirst();
                }
                column++;
            }
            QStandardItem *checkbox = new QStandardItem(true);
            checkbox->setEditable(false);
            checkbox->setCheckable(true);
            checkbox->setCheckState(Qt::Unchecked);
            myModel.setItem(row, column, checkbox);

            tableData.proteins.removeFirst();
            row++;
        }
    }

    if(!tableData.psm.isEmpty()){
        peptideModel.setHorizontalHeaderLabels(HeaderPadding + tableData.psm.first() + QStringList(""));
        tableData.psm.removeFirst();

        int row = 0;
        while(!tableData.psm.isEmpty()){
            int column = 0;
            while(!tableData.psm.first().isEmpty()){
                if(column == 0){
                    QStandardItem *rowNum = new QStandardItem(0);
                    rowNum->setData(row+1, Qt::DisplayRole);
                    rowNum->setEditable(false);
                    peptideModel.setItem(row, column, rowNum);
                } else if(column == 1){
                    QStandardItem *star = new QStandardItem(true);
                    star->setEditable(false);
                    star->setCheckable(true);
                    star->setCheckState(Qt::Unchecked);
                    peptideModel.setItem(row, column, star);
                } else if(column >= 3){
                    QStandardItem *data = new QStandardItem(0);
                    data->setData(tableData.psm.first().first(), Qt::DisplayRole);
                    data->setEditable(false);
                    peptideModel.setItem(row, column, data);
                    tableData.psm.first().removeFirst();
                }
                column++;
            }
            QStandardItem *checkbox = new QStandardItem(true);
            checkbox->setEditable(false);
            checkbox->setCheckable(true);
            checkbox->setCheckState(Qt::Unchecked);
            peptideModel.setItem(row, column, checkbox);

            tableData.psm.removeFirst();
            row++;
        }
    }

    //list of columns with bars
//    const QList<int> barList = {5,6,7,8,9,10,11};
//    const QList<int> peptideBarList = {5,6};

    //Link view to model
    tableView.setModel( &myModel );
    tableViewPeptides.setModel(&peptideModel);

//    foreach (int i, barList) {
//        tableView.setItemDelegateForColumn(i, new barDelegate);
//    }

    tableView.setItemDelegateForColumn(myModel.columnCount()-1, new BooleanDelegate);
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
