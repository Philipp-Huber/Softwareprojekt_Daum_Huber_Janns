
#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    :QAbstractTableModel(parent)
    {
    //initializeCheckMarks();
    for(int i = 0; i < rowCount(); i++)
    {
        for(int j = 0; j < columnCount(); j++)
        {
            QModelIndex ind = this->index(i,j,QModelIndex());

            if(ind.column() == 12){
                setData(ind, static_cast<QVariant>(false), Qt::DisplayRole);
            } else {
                setData(ind, static_cast<QVariant>(0), Qt::DisplayRole);
            }
        }
    }
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

//void MyModel::initializeCheckMarks(){
//    checkMarks = QVector<bool>(rowCount());
//}

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
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        return index.data(role);
//        if(index.row() == 0)
//        {
//            //return QVariant(); //Feed data here
//            if(index.column() == 12)
//            {
//                return QVariant::fromValue(checkMarks[index.row()]);
//            }
//        }
    }

    return QVariant();

}

//Write data to model
void MyModel::setData(const QModelIndex &index, const QVariant &value, int role) const
{
    index.data(role) = value;
//    if(index.column() == 12 && role == Qt::EditRole)
//    {
        //checkMarks.at(index.row()) = value.toBool();
//    }
}
