
#include <QAbstractTableModel>

namespace Ui {
class MainWindow;
}

class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    std::vector<bool> checkMarks;

    MyModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    void initializeCheckMarks();
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

};

Q_DECLARE_METATYPE(std::vector<bool>*)
