#ifndef PEPTIDEVIEW_H
#define PEPTIDEVIEW_H

#include <QTableView>
#include <QObject>

class PeptideView : public QTableView
{
    Q_OBJECT

public:
    PeptideView();

private:
   QList<int> displayThese;

public slots:
    void toBeDisplayed(QModelIndex index);
};

#endif // PEPTIDEVIEW_H
