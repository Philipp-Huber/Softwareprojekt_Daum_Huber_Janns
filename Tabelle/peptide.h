#ifndef PEPTIDE_H
#define PEPTIDE_H

#include <QObject>

class Peptide : public QObject
{
    Q_OBJECT

protected:
    int pl;
    QString sequence;
    int start;
    int spectraNumber;
    double confidence;
    bool checked;



public:
    void setPl(int);
    void setSequence(QString);
    void setStart(int);
    void setSpectraNumber(int);
    void setConfidence(double);
    void setChecked(bool);

    int getPl();
    QString getSequence();
    int getStart();
    int getSpectraNumber();
    double getConfidence();
    bool isChecked();
    explicit Peptide(QObject *parent = 0);


public slots:
    //void updateDisplayed(bool);

};

#endif // PEPTIDE_H
