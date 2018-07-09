#include <QApplication>
#include <QWindow>
#include <QSplitter>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QtWidgets/QTableView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "mzfileloader.h" 
#include "qcustomsortfilterproxymodel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    QTableView tableViewPeptides;
    mzFileLoader loader;
    QPushButton button("Load File...");
    QCustomSortFilterProxyModel proxyModel;
    QComboBox filterBox;
    QLineEdit filterText("Search");


    //Make instance of models
    QStandardItemModel proteinModel(0);
    QStandardItemModel peptideModel(0);

    //Make tableviews and models known to loader
    loader.setTableViews(&tableView, &tableViewPeptides);
    loader.setModels(&proteinModel, &peptideModel);

    //Link view to model
    proxyModel.setSourceModel(&proteinModel);
    tableView.setModel( &proxyModel );
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    tableViewPeptides.setModel( &peptideModel );
    tableViewPeptides.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //Make Filter Widget
    QSplitter *filter = new QSplitter();
    filter->setOrientation(Qt::Horizontal);

//    filterBox.addItem("test 1");
//    filterBox.addItem("test 2");
//    filterBox.addItem("test 3");
//    filterBox.addItem("test 4");

    filter->addWidget(&filterBox);
    filter->addWidget(&filterText);

    //Filter
//    proxyModel.setFilterRegExp(QRegExp(filterText.text(),Qt::CaseInsensitive));
    proxyModel.setFilterKeyColumn(0);

    //Connect everything
    loader.connect(&loader, SIGNAL(clearComboBox()), &filterBox, SLOT(clear()));
    loader.connect(&loader, &mzFileLoader::HeaderDataChanged, &filterBox, &QComboBox::addItems);
    button.connect(&button, SIGNAL(clicked()), &loader, SLOT(load()));
    filterText.connect(&filterText, &QLineEdit::textEdited, &proxyModel, &QSortFilterProxyModel::setFilterFixedString);
    filterBox.connect(&filterBox, SIGNAL(currentIndexChanged(int)), &proxyModel, SLOT(changeFilterKeyColumn(int)));

    //Display
    QSplitter *splitter = new QSplitter();
    splitter->setOrientation(Qt::Vertical);

    splitter->addWidget(&button);
    splitter->addWidget(filter);
    splitter->addWidget(&tableView);
    splitter->addWidget(&tableViewPeptides);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    splitter->setWindowTitle("Bars and Checkboxes");
    splitter->show();

    return a.exec();
}
