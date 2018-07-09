#include <QApplication>
#include <QWindow>
#include <QSplitter>
#include <QPushButton>
#include <QLineEdit>
#include <QtWidgets/QTableView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "mzfileloader.h" 



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    QTableView tableViewPeptides;
    mzFileLoader loader;
    QSortFilterProxyModel proxyModle;


    //Make instance of models
    QStandardItemModel proteinModel(0);
    QStandardItemModel peptideModel(0);

    //Make tableviews and models known to loader
    loader.setTableViews(&tableView, &tableViewPeptides);
    loader.setModels(&proteinModel, &peptideModel);

    //Link view to model
    proxyModle.setSourceModel(&proteinModel);
    tableView.setModel( &proxyModle );
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    tableViewPeptides.setModel( &peptideModel );
    tableViewPeptides.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //Make Load button
    QPushButton button("Load File...");
    button.connect(&button, &QPushButton::clicked, &loader, &mzFileLoader::load);

    //Make Filter Text Field
    QLineEdit filter("2");

    //Filter
    proxyModle.setFilterRegExp(QRegExp(filter.text(),Qt::CaseInsensitive));
    proxyModle.setFilterKeyColumn(0);

    //Display
    QSplitter *splitter = new QSplitter();
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(&filter);
    splitter->addWidget(&button);
    splitter->addWidget(&tableView);
    splitter->addWidget(&tableViewPeptides);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    splitter->setWindowTitle("Bars and Checkboxes");
    splitter->show();

    return a.exec();
}
