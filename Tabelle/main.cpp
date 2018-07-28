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
#include "markdelegate.h"
#include "star.h"
#include "mzparser.h"
#include "peptideview.h"
#include "proteinview.h"
#include "mzfileloader.h" 
#include "qcustomsortfilterproxymodel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//---------------------------------------------------------------<< Initialize Objects >>-----------------------------------------------------------------------------


    ProteinView tableViewProteins;
    //set the allowed selections to rows only
    tableViewProteins.setSelectionBehavior(QAbstractItemView::SelectRows);
    //allow any subset of rows to be selected at once
    tableViewProteins.setSelectionMode(QAbstractItemView::MultiSelection);

    PeptideView tableViewPeptides;


    mzFileLoader loader;
    QPushButton button("Load File...");
    QCustomSortFilterProxyModel proteinProxy;
    QCustomSortFilterProxyModel proteinProxy2;
    QCustomSortFilterProxyModel proteinProxy3;
    QCustomSortFilterProxyModel proteinProxyFinal;
    QSortFilterProxyModel peptideProxy; //needed for sortable columns
    QComboBox filterBox;
    QComboBox filterBox2;
    QComboBox filterBox3;
    QComboBox filterBoxFinal;
    QLineEdit filterText("Search");
    QLineEdit filterText2("Search");
    QLineEdit filterText3("Search");
    QLineEdit filterTextFinal("Search");
    QPushButton clearButtonProteins("Clear selection");
    QPushButton clearButtonPeptides("Clear selection");

    //Make instance of models
    QStandardItemModel proteinModel(0);
    QStandardItemModel peptideModel(0);

    //Make tableviews and models known to loader
    loader.setTableViews(&tableViewProteins, &tableViewPeptides);
    loader.setModels(&proteinModel, &peptideModel);
    loader.setProxies(&proteinProxyFinal, &peptideProxy);

    //initiate Proxys
    proteinProxyFinal.setSourceModel( &proteinProxy3 );
    proteinProxy3.setSourceModel( &proteinProxy2 );
    proteinProxy2.setSourceModel( &proteinProxy );
    proteinProxy.setSourceModel( &proteinModel );

    peptideProxy.setSourceModel( &peptideModel );

    //Link view to models
    tableViewProteins.setModel( &proteinModel );
    tableViewProteins.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    tableViewPeptides.setModel( &peptideModel );
    tableViewPeptides.setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);


    //Filter
//    proxyModel.setFilterRegExp(QRegExp(filterText.text(),Qt::CaseInsensitive));
    proteinProxyFinal.setFilterKeyColumn(0);
    proteinProxy3.setFilterKeyColumn(0);
    proteinProxy2.setFilterKeyColumn(0);
    proteinProxy.setFilterKeyColumn(0);


//---------------------------------------------------------------<< Connections >>-----------------------------------------------------------------------------


    //Link protein table selection with displayed peptides
    QObject::connect(&tableViewProteins, SIGNAL(activeAccessions(QList<QString>)),
            &tableViewPeptides, SLOT(toBeDisplayed(QList<QString>)));

    //Loader communication
    QObject::connect(tableViewProteins.horizontalHeader(), &QHeaderView::sortIndicatorChanged, &loader, &mzFileLoader::catchInvalidSortIndicator);
    QObject::connect(tableViewPeptides.horizontalHeader(), &QHeaderView::sortIndicatorChanged, &loader, &mzFileLoader::catchInvalidSortIndicator);
    loader.connect(&loader, SIGNAL(clearComboBox()), &filterBox, SLOT(clear()));
    loader.connect(&loader, &mzFileLoader::HeaderDataChanged, &filterBox, &QComboBox::addItems);
    loader.connect(&loader, SIGNAL(clearComboBox()), &filterBox2, SLOT(clear()));
    loader.connect(&loader, &mzFileLoader::HeaderDataChanged, &filterBox2, &QComboBox::addItems);
    loader.connect(&loader, SIGNAL(clearComboBox()), &filterBox3, SLOT(clear()));
    loader.connect(&loader, &mzFileLoader::HeaderDataChanged, &filterBox3, &QComboBox::addItems);
    loader.connect(&loader, SIGNAL(clearComboBox()), &filterBoxFinal, SLOT(clear()));
    loader.connect(&loader, &mzFileLoader::HeaderDataChanged, &filterBoxFinal, &QComboBox::addItems);
    button.connect(&button, SIGNAL(clicked()), &loader, SLOT(load()));

    //User Input updating Filters
    QObject::connect(&filterText, SIGNAL(textEdited(QString)), &proteinProxy, SLOT(customSetFilterFixedString(QString)));
    filterBox.connect(&filterBox, SIGNAL(currentIndexChanged(int)), &proteinProxy, SLOT(changeFilterKeyColumn(int)));
    QObject::connect(&filterText2, SIGNAL(textEdited(QString)), &proteinProxy2, SLOT(customSetFilterFixedString(QString)));
    filterBox2.connect(&filterBox2, SIGNAL(currentIndexChanged(int)), &proteinProxy2, SLOT(changeFilterKeyColumn(int)));
    QObject::connect(&filterText3, SIGNAL(textEdited(QString)), &proteinProxy3, SLOT(customSetFilterFixedString(QString)));
    filterBox.connect(&filterBox3, SIGNAL(currentIndexChanged(int)), &proteinProxy3, SLOT(changeFilterKeyColumn(int)));
    QObject::connect(&filterTextFinal, SIGNAL(textEdited(QString)), &proteinProxyFinal, SLOT(customSetFilterFixedString(QString)));
    filterBox.connect(&filterBoxFinal, SIGNAL(currentIndexChanged(int)), &proteinProxyFinal, SLOT(changeFilterKeyColumn(int)));

    //Filters updating tableViewProteins
    QObject::connect(&proteinProxy, SIGNAL(modelUpdated()), &tableViewProteins, SLOT(updateEvent()));
    QObject::connect(&proteinProxy2, SIGNAL(modelUpdated()), &tableViewProteins, SLOT(updateEvent()));
    QObject::connect(&proteinProxy3, SIGNAL(modelUpdated()), &tableViewProteins, SLOT(updateEvent()));
    QObject::connect(&proteinProxyFinal, SIGNAL(modelUpdated()), &tableViewProteins, SLOT(updateEvent()));

    //clearButtons clear the selection in the respective View
    QObject::connect(&clearButtonProteins, SIGNAL(clicked()), &tableViewProteins, SLOT(clearSelection()));
    QObject::connect(&clearButtonPeptides, SIGNAL(clicked()), &tableViewPeptides, SLOT(clearSelection()));


//---------------------------------------------------------------<< UI Layout >>-----------------------------------------------------------------------------

    QWidget *dynamicPadding1 = new QWidget;
    QWidget *dynamicPadding2 = new QWidget;
    QWidget *dynamicPadding3 = new QWidget;
    QWidget *dynamicPadding4 = new QWidget;
    QWidget *dynamicPadding5 = new QWidget;

    //Make splitter containing
    QSplitter *splitter = new QSplitter();
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(&button);
    splitter->addWidget(&clearButtonProteins);
    splitter->addWidget(&tableViewProteins);
    splitter->addWidget(&clearButtonPeptides);
    splitter->addWidget(&tableViewPeptides);

    //Make splitter that contains search line and selection box for first filter
    QSplitter *filter1 = new QSplitter();
    filter1->setOrientation(Qt::Horizontal);
    filter1->addWidget(&filterBox);
    filter1->addWidget(&filterText);

    //Make splitter that contains search line and selection box for second filter
    QSplitter *filter2 = new QSplitter();
    filter2->setOrientation(Qt::Horizontal);
    filter2->addWidget(&filterBox2);
    filter2->addWidget(&filterText2);

    //Make splitter that contains search line and selection box for third filter
    QSplitter *filter3 = new QSplitter();
    filter3->setOrientation(Qt::Horizontal);
    filter3->addWidget(&filterBox3);
    filter3->addWidget(&filterText3);

    //Make splitter that contains search line and selection box for final filter
    QSplitter *filterFinal = new QSplitter();
    filterFinal->setOrientation(Qt::Horizontal);
    filterFinal->addWidget(&filterBoxFinal);
    filterFinal->addWidget(&filterTextFinal);

    //Make bar of all filters
    QSplitter *proteinFilter = new QSplitter();
    proteinFilter->setOrientation(Qt::Vertical);
    proteinFilter->addWidget(dynamicPadding1);
    proteinFilter->addWidget(filter1);
    proteinFilter->addWidget(dynamicPadding2);
    proteinFilter->addWidget(filter2);
    proteinFilter->addWidget(dynamicPadding3);
    proteinFilter->addWidget(filter3);
    proteinFilter->addWidget(dynamicPadding4);
    proteinFilter->addWidget(filterFinal);
    proteinFilter->addWidget(dynamicPadding5);

    proteinFilter->setStretchFactor(0,2);
    proteinFilter->setStretchFactor(1,0);
    proteinFilter->setStretchFactor(2,1);
    proteinFilter->setStretchFactor(3,0);
    proteinFilter->setStretchFactor(4,1);
    proteinFilter->setStretchFactor(5,0);
    proteinFilter->setStretchFactor(6,1);
    proteinFilter->setStretchFactor(7,0);
    proteinFilter->setStretchFactor(8,10);


    //Display
    QSplitter *frame = new QSplitter();
    frame->setOrientation(Qt::Horizontal);
    frame->addWidget(splitter);
    frame->addWidget(proteinFilter);

    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    frame->setWindowTitle("Bars and Checkboxes");
    frame->show();

    frame->setStretchFactor(0,1);
    frame->setStretchFactor(1,0);
    return a.exec();
}
