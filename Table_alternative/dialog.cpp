#include "dialog.h"
#include "ui_dialog.h"

DelegateTableViewDialog
    ::DelegateTableViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelegateTableViewDialog)
{
    ui->setupUi(this);

    checkboxdelegate = new CheckBoxDelegate(this);

    // Create a new model
    // QStandardItemModel(int rows, int columns, QObject * parent = 0)
    model = new TableModel();

    // Attach the model to the view
    ui->tableView->setModel(model);

    // Tie the View with the new MyDelegate instance
    // If we don not set this, it will use default delegate
    ui->tableView->setItemDelegate(checkboxdelegate);
}

DelegateTableViewDialog::~DelegateTableViewDialog()
{
    delete ui;
}
