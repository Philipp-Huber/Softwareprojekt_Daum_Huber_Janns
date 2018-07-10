#ifndef PROTEINVIEW_H
#define PROTEINVIEW_H

#include<QTableView>
#include<QObject>

class ProteinView : public QTableView
{
    Q_OBJECT

public:
    ProteinView();

signals:
    void activeAccessions(QList<QString>);

private slots:
    void selectionEvent(QModelIndex);

};

#endif // PROTEINVIEW_H
