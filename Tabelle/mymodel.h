
#include <QAbstractTableModel>

namespace Ui {
class MainWindow;
}

class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MyModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

};
