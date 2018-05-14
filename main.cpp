#include <QCoreApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream out(stdout);
    out << "HELLO WORLD!!!" << endl;

    return a.exec();
}
