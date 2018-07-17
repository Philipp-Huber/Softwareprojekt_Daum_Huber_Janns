#ifndef QCUSTOMSORTFILTERPROXYMODEL_H
#define QCUSTOMSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class QCustomSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit QCustomSortFilterProxyModel(QObject *parent = 0);

signals:

public slots:
    void changeFilterKeyColumn(int col){
        this->setFilterKeyColumn(col);
    }

};

#endif // QCUSTOMSORTFILTERPROXYMODEL_H
