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
            if(columns == 12){
                //Create checkbox item
                QStandardItem* checkbox = new QStandardItem(true);
                //This item must not be editable, otherwise the app crashes when you double-click the item
                checkbox->setEditable(false);
                checkbox->setCheckable(true);
                checkbox->setCheckState(Qt::Unchecked);
                //Insert
                myModel.setItem(rows, columns, checkbox);
            } else {
                QStandardItem* integer = new QStandardItem(0);
                integer->setData(10, Qt::DisplayRole);
                integer->setEditable(true);
                myModel.setItem(rows, columns, integer);
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

    //Link view to model
    tableView.setModel( &myModel );
    tableView.setItemDelegate(new barDelegate);
    tableView.setItemDelegateForColumn(12, new BooleanDelegate);
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //Display
    tableView.setWindowTitle("Bars and Checkboxes");
    tableView.show();

    return a.exec();
}
