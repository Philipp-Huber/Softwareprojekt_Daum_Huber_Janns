

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
    return 5;
}
//columns in table
int MyModel::columnCount(const QModelIndex & /*parent*/) const{
    return 13;
}

//fills in column headers
QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            return columnHeaders[section];
        }
    }

        return QVariant();
}


//fill table with data
QVariant MyModel::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            break;

        case 8:
            break;

        case 9:
            break;

        case 10:
            break;

        case 11:
            break;

        case 12:
            return index.row()*10;
            break;
        }
    }
    return QVariant();

}
