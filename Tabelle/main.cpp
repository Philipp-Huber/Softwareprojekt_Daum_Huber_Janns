#include <QApplication>
#include <QWindow>
#include <QSplitter>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QtWidgets/QTableView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include "booleaneditor.h"
#include "barDelegate.h"
#include "star.h"
#include "mzparser.h"
#include "peptideview.h"
#include "proteinview.h"
#include "mzfileloader.h" 
#include "qcustomsortfilterproxymodel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProteinView tableView;
    //set the allowed selections to rows only
    tableView.setSelectionBehavior(QAbstractItemView::SelectRows);
    //allow any subset of rows to be selected at once
    tableView.setSelectionMode(QAbstractItemView::MultiSelection);

    PeptideView tableViewPeptides;

    mzFileLoader loader;
    QPushButton button("Load File...");
    QCustomSortFilterProxyModel proxyModel;
    QComboBox filterBox;
    QLineEdit filterText("Search");



    //Make instance of models
    QStandardItemModel proteinModel(0);
    QStandardItemModel peptideModel(0);

    //link protein table selection with displayed peptides
    QObject::connect(&tableView, SIGNAL(activeAccessions(QList<QString>)),
            &tableViewPeptides, SLOT(toBeDisplayed(QList<QString>)));

   // QObject::connect(&tableView, SIGNAL(starKliked(int)),
   //             &tableView, SLOT(starRow(int)));

    //Make tableviews and models known to loader
    loader.setTableViews(&tableView, &tableViewPeptides);
    loader.setModels(&proteinModel, &peptideModel);

    //Link view to model
    proxyModel.setSourceModel(&proteinModel);
    tableView.setModel( &proxyModel );
    tableView.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    tableViewPeptides.setModel( &peptideModel );
    tableViewPeptides.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    //Make splitter that contains search line and selection box
    QSplitter *filter = new QSplitter();
    filter->setOrientation(Qt::Horizontal);

    filter->addWidget(&filterBox);
    filter->addWidget(&filterText);

    //Filter
//    proxyModel.setFilterRegExp(QRegExp(filterText.text(),Qt::CaseInsensitive));
    proxyModel.setFilterKeyColumn(0);

    //Connect everything
    loader.connect(&loader, SIGNAL(clearComboBox()), &filterBox, SLOT(clear()));
    loader.connect(&loader, &mzFileLoader::HeaderDataChanged, &filterBox, &QComboBox::addItems);
    button.connect(&button, SIGNAL(clicked()), &loader, SLOT(load()));
    QObject::connect(&filterText, SIGNAL(textEdited(QString)), &proxyModel, SLOT(customSetFilterFixedString(QString)));
    filterBox.connect(&filterBox, SIGNAL(currentIndexChanged(int)), &proxyModel, SLOT(changeFilterKeyColumn(int)));
    QObject::connect(&proxyModel, SIGNAL(modelUpdated()), &tableView, SLOT(updateEvent()));

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
