
#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    :QAbstractTableModel(parent)
    {
    initializeCheckMarks();
}

//Array containing the header names
const QString columnHeaders[13] = {
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

//rows in table
int MyModel::rowCount(const QModelIndex & /*parent*/) const{
    return 1;
}
//columns in table
int MyModel::columnCount(const QModelIndex & /*parent*/) const{
    return 13;
}

void MyModel::initializeCheckMarks(){
    for(int i = 0; i < rowCount(); i++){
        checkMarks.push_back(false);
    }
}

// Orientation useless as of yet, may come in handy for user customization though
//fills in column headers
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole)
    {
        return columnHeaders[section];
    }

        return QVariant();
}


//fill table with data
QVariant MyModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole)
    {
        if(index.row() == 0)
        {
            //return QVariant(); //Feed data here
        }

        if(index.column() == 12)
        {
            return QVariant::fromValue(checkMarks[index.row()]);
        }
    }

//    if(role == Qt::EditRole)
//    {
//        if(index.column() == 12)
//        {
//            checkMarks[index.row()] = index.data().toBool();
//        }
//    }
    return QVariant();

}
