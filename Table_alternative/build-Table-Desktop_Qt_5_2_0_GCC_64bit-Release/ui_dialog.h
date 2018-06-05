/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_DelegateTableViewDialog
{
public:
    QTableView *tableView;

    void setupUi(QDialog *DelegateTableViewDialog)
    {
        if (DelegateTableViewDialog->objectName().isEmpty())
            DelegateTableViewDialog->setObjectName(QStringLiteral("DelegateTableViewDialog"));
        DelegateTableViewDialog->resize(1330, 300);
        tableView = new QTableView(DelegateTableViewDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 0, 1329, 299));

        retranslateUi(DelegateTableViewDialog);

        QMetaObject::connectSlotsByName(DelegateTableViewDialog);
    } // setupUi

    void retranslateUi(QDialog *DelegateTableViewDialog)
    {
        DelegateTableViewDialog->setWindowTitle(QApplication::translate("DelegateTableViewDialog", "Table", 0));
    } // retranslateUi

};

namespace Ui {
    class DelegateTableViewDialog: public Ui_DelegateTableViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
