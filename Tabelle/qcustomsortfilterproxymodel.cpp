#include "qcustomsortfilterproxymodel.h"

QCustomSortFilterProxyModel::QCustomSortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    QObject::connect(this, SIGNAL(updateFilter(QString)),
                     this, SLOT(setFilterFixedString(QString)));//, static_cast<Qt::ConnectionType>(Qt::BlockingQueuedConnection | Qt::UniqueConnection));
}

void QCustomSortFilterProxyModel::customSetFilterFixedString(QString pattern){
    emit updateFilter(pattern);
    emit modelUpdated();
}
