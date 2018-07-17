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
   QList<QString> displayThese;

public slots:
    void toBeDisplayed(QList<QString>);
};

#endif // PEPTIDEVIEW_H
