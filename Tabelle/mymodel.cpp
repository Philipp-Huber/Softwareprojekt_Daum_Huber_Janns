
#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    :QAbstractTableModel(parent)
    {
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

//fill table with data
QVariant MyModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole)
    {
        if(index.row() == 0)
        {
            return columnHeaders[index.column()];
        }
    }
    return QVariant();

}
