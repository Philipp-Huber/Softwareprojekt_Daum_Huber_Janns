#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QCheckBox>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<QCheckBox> getCheckBoxes();

private:
    QList<QCheckBox> checkboxes;
    int rowCountInt = 2;
    int columnCountInt = 13;
    const QStringList columnHeaders = {
        "",
        "",
        "Pl",
        "Accession",
        "Description",
        "Chr",
        "Coverage",
        "#Peptides",
        "#Spectra",
        "MS2 quant",
        "MW",
        "Confidence",
        ""
    };
};

Q_DECLARE_METATYPE(QCheckBox)
#endif // TABLEMODEL_H
