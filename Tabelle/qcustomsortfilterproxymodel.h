#ifndef QCUSTOMSORTFILTERPROXYMODEL_H
#define QCUSTOMSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class QCustomSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit QCustomSortFilterProxyModel(QObject *parent = 0);


signals:
    void modelUpdated();
    void updateFilter(QString);

public slots:
    void changeFilterKeyColumn(int col){
        this->setFilterKeyColumn(col);
    }

    void customSetFilterFixedString(QString);
};

#endif // QCUSTOMSORTFILTERPROXYMODEL_H
