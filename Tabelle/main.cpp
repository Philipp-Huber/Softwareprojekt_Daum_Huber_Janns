#include <QApplication>
#include <QWindow>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include "booleaneditor.h"
#include "barDelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;

    //Make instance of model
    QStandardItemModel myModel(0);

    //Fill model with data (generic for now)
    for(int rows = 0; rows < 3; rows++){
        for(int columns = 0; columns < 13; columns++){
            if(columns == 12 || columns == 1){
                //Create checkbox item
                QStandardItem* checkbox = new QStandardItem(true);
                //This item must not be editable, otherwise the app crashes when you double-click the item
                checkbox->setEditable(false);
                checkbox->setCheckable(true);
                checkbox->setCheckState(Qt::Unchecked);
                //Insert
                myModel.setItem(rows, columns, checkbox);
            } else if (columns == 0){
                QStandardItem* row = new QStandardItem(0);
                row -> setData(rows + 1, Qt::DisplayRole);
                row -> setEditable(false);
                myModel.setItem(rows, columns, row);
            }


            else {
                QStandardItem* percentage = new QStandardItem(0);
                percentage->setData(0.3f, Qt::DisplayRole);
                percentage->setEditable(true);
                myModel.setItem(rows, columns, percentage);
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

    //list of columns with bars
    const QList<int> barList = {5,6,7,8,9,10,11};

    //Link view to model
    tableView.setModel( &myModel );
    foreach (int i, barList) {
        tableView.setItemDelegateForColumn(i, new barDelegate);
    }

    tableView.setItemDelegateForColumn(12, new BooleanDelegate);
    tableView.setItemDelegateForColumn(1, new BooleanDelegate);
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //Display
    tableView.setWindowTitle("Bars and Checkboxes");
    tableView.show();

    return a.exec();
}
