#ifndef PROTEIN_H
#define PROTEIN_H

#include <QObject>

class Protein : public QObject
{
    Q_OBJECT

protected:
    QString accession;
    QString description;
    int chr;
    double coverage;
    int peptideNumber;
    int spectraNumber;
    double ms2Quant;
    double meanValue;
    double confidence;

public:
    explicit Protein(QObject *parent = 0);

    void setAccession(QString);
    void setDescription(QString);
    void setChr(int);
    void setPeptideNumber(int);
    void setSpectraNumber(int);
    void setMs2Quant(double);
    void setMeanValue(double);
    void setConfidence(double);
    void setChecked(bool);

    QString getAccession();
    QString getDescription();
    int getChr();
    double getCoverage();
    int getPeptideNumber();
    int getSpectraNumber();
    double getMs2Quant();
    double getMeanValue();
    double getConfidence();



public slots:

};

#endif // PROTEIN_H
