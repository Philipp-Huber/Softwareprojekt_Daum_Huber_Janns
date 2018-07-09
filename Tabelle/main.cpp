#include <QApplication>
#include <QWindow>
#include <QSplitter>
#include <QPushButton>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include "mzfileloader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    QTableView tableViewPeptides;
    mzFileLoader loader;

    //Make instance of models
    QStandardItemModel proteinModel(0);
    QStandardItemModel peptideModel(0);

    //Make tableviews and models known to loader
    loader.setTableViews(&tableView, &tableViewPeptides);
    loader.setModels(&proteinModel, &peptideModel);

    //Link view to model
    tableView.setModel( &proteinModel );
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    tableViewPeptides.setModel( &peptideModel );
    tableViewPeptides.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //Make Load button
    QPushButton button("Load File...");
    button.connect(&button, &QPushButton::clicked, &loader, &mzFileLoader::load);

    //Display
//    tableView.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    tableViewPeptides.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QSplitter *splitter = new QSplitter();
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(&button);
    splitter->addWidget(&tableView);
    splitter->addWidget(&tableViewPeptides);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    splitter->setWindowTitle("Bars and Checkboxes");
    splitter->show();

    return a.exec();
}
