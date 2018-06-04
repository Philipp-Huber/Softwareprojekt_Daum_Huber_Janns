#ifndef DELEGATETABLEVIEWDIALOG_H
#define DELEGATETABLEVIEWDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QStringList>
#include "checkboxdelegate.h"
#include "tablemodel.h"

namespace Ui {
class DelegateTableViewDialog;
}

class DelegateTableViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelegateTableViewDialog(QWidget *parent = 0);
    ~DelegateTableViewDialog();

private:
    Ui::DelegateTableViewDialog *ui;

    // QStandardItemModel provides a classic
    // item-based approach to working with the model.
    TableModel *model;

    // Make a member pointer to a new MyDelegate instance
    CheckBoxDelegate *checkboxdelegate;
};

#endif // DELEGATETABLEVIEWDIALOG_H
