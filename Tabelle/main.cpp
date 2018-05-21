#include <QApplication>
#include <QtWidgets/QTableView>
#include "mymodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;

    //make instance of model
    MyModel myModel(0);

    //make tableView create table (invokes functions in mymodel.cpp)
    tableView.setModel( &myModel );

    //displays
    tableView.show();

    return a.exec();
}
