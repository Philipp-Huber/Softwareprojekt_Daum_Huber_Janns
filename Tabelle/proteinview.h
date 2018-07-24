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

    /*!
     * \brief The clearAllStars function sets all stars in column 1 as unchecked
     *
     * The function considers the first column to only hold star objects, which state is either checked or unchecked. It sets the state of every object in this column to unchecked.
     */
    void clearAllStars();

signals:
    void released();
    void activeAccessions(QList<QString>);

public slots:
    void updateEvent();
   // void starRow(int);

};

#endif // PROTEINVIEW_H
