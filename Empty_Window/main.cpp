#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    window.resize(320,240);
    window.show();
    window.setWindowTitle("Our first window");

    return a.exec();
}
