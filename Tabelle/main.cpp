#include <QApplication>
#include <QtWidgets/QTableView>
#include "mymodel.h"
#include "barDelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;

    //make instance of model
    MyModel myModel(0);

    //make tableView create table (invokes functions in mymodel.cpp)
    tableView.setModel( &myModel );

    barDelegate delegate;
    tableView.setItemDelegate(&delegate);

//    tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);

    //displays
    tableView.setWindowTitle("Bars");
    tableView.show();

    return a.exec();
}
