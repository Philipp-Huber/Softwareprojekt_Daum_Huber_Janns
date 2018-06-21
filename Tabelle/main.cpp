#include <QApplication>
#include <QWindow>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include "booleaneditor.h"
#include "barDelegate.h"
#include "star.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    QTableView tableView;
    QTableView tableViewPeptides;

    //Make instance of models
    QStandardItemModel myModel(0);
    QStandardItemModel peptideModel(0);

    //Fill protein model with data (generic for now)
    for(int rows = 0; rows < 3; rows++){
        for(int columns = 0; columns < 13; columns++){
            if(columns == 1){
                //Create checkbox item
                QStandardItem* star = new QStandardItem(true);
                //This item must not be editable, otherwise the app crashes when you double-click the item
                star->setEditable(false);
                star->setCheckable(true);
                star->setCheckState(Qt::Unchecked);
                //Insert
                myModel.setItem(rows, columns, star);
            }else if(columns == 12){
                //Create checkbox item
                QStandardItem* checkbox = new QStandardItem(true);
                //This item must not be editable, otherwise the app crashes when you double-click the item
                checkbox->setEditable(false);
                checkbox->setCheckable(true);
                checkbox->setCheckState(Qt::Unchecked);
                //Insert
                myModel.setItem(rows, columns, checkbox);
            }else if (columns == 0){
                QStandardItem* row = new QStandardItem(0);
                row -> setData(rows + 1, Qt::DisplayRole);
                row -> setEditable(false);
                myModel.setItem(rows, columns, row);
            }

            // This item should only be edibal for testing
            else {
                QStandardItem* percentage = new QStandardItem(0);
                percentage->setData(0.3f, Qt::DisplayRole);
                percentage->setEditable(false);
                myModel.setItem(rows, columns, percentage);
            }
        }
    }

    //Fill peptide model with data (also generic)
    for(int rows = 0; rows < 1; rows++){
        for(int columns = 0; columns < 8; columns++){
            if(columns == 1 || columns == 7){
                //Create checkbox item
                QStandardItem* checkbox = new QStandardItem(true);
                //This item must not be editable, otherwise the app crashes when you double-click the item
                checkbox->setEditable(false);
                checkbox->setCheckable(true);
                checkbox->setCheckState(Qt::Unchecked);
                //Insert
                peptideModel.setItem(rows, columns, checkbox);
            }
            else if (columns == 0){
                QStandardItem* row = new QStandardItem(0);
                row -> setData(rows + 1, Qt::DisplayRole);
                row -> setEditable(false);
                peptideModel.setItem(rows, columns, row);
            }
            else {
                QStandardItem *item = new QStandardItem(0);
                item->setData(0.3f, Qt::DisplayRole);
                item->setEditable(false);
                peptideModel.setItem(rows, columns, item);
            }
        }
    }

    //Column headers constant for proteins
    const QStringList columnHeaders = {
        "",
        "",
        "Pl",
        "Accession",
        "Description",
        "Chr",
        "Coverage",
        "#Peptides",
        "#Spectra",
        "MS2 quant",
        "MW",
        "Confidence",
        ""};
    //Set header names
    myModel.setHorizontalHeaderLabels(columnHeaders);

    //Column headers constant for peptides
    const QStringList columnPeptides = {
        "",
        "",
        "Pl",
        "Sequence",
        "Start",
        "#Spectra",
        "Confidence",
        ""
    };
    peptideModel.setHorizontalHeaderLabels(columnPeptides);

    //list of columns with bars
    const QList<int> barList = {5,6,7,8,9,10,11};
    const QList<int> peptideBarList = {5,6};

    //Link view to model
    tableView.setModel( &myModel );
    tableViewPeptides.setModel(&peptideModel);

    foreach (int i, barList) {
        tableView.setItemDelegateForColumn(i, new barDelegate);
    }

    tableView.setItemDelegateForColumn(12, new BooleanDelegate);
    tableView.setItemDelegateForColumn(1, new starDelegate);
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    foreach(int i, peptideBarList){
        tableViewPeptides.setItemDelegateForColumn(i, new barDelegate);
    }

    tableViewPeptides.setItemDelegateForColumn(7, new BooleanDelegate);
    tableViewPeptides.setItemDelegateForColumn(1, new BooleanDelegate);
    tableViewPeptides.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //Display
    tableView.setParent(&window);
    tableView.setGeometry(0, 0, 1320, 250);
    tableViewPeptides.setParent(&window);
    tableViewPeptides.setGeometry(0, 253, 820, 250);
    window.setWindowTitle("Bars and Checkboxes");
    window.show();

    return a.exec();
}
