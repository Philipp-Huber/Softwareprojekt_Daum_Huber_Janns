#include <QApplication>
#include <QtWidgets/QTableView>
#include "mymodel.h"
#include "booleaneditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;

    //make instance of model
    MyModel myModel(0);

    //make tableView create table (invokes functions in mymodel.cpp)
    tableView.setModel( &myModel );
    tableView.setItemDelegate(new BooleanEditor);
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //displays
    tableView.show();

    return a.exec();
}
