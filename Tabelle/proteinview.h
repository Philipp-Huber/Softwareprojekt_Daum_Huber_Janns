#ifndef PROTEINVIEW_H
#define PROTEINVIEW_H

#include<QTableView>
#include<QObject>

class ProteinView : public QTableView
{
    Q_OBJECT

public:
    ProteinView();

protected:
    bool eventFilter(QObject*, QEvent*) override;

signals:
    void released();
    void activeAccessions(QList<QString>);

private slots:
    void selectionEvent();

};

#endif // PROTEINVIEW_H
