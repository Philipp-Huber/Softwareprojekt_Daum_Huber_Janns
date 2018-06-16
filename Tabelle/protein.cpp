#include "protein.h"

Protein::Protein(QObject *parent) :
    QObject(parent)
{
}


void Protein::setChecked(bool checked){
    if(this->checked != checked){
        this->checked = checked;
        emit checkedChanged(checked);
    }
}

void Protein::connectAllChildren(){
    QList<QObject> allChildren;
    allChildren = findChildren<QObject>();
//    foreach (QObject child, allChildren)
//    {
//        QObject::connect(this, SIGNAL(checkedChanged(bool)),
//                        &child, SLOT(updateDisplayed(bool)));
//    }
}


//getter and setter
void Protein::setAccession(QString acc){
    this->accession = acc;
}

void Protein::setDescription(QString desc){
    this->description = desc;
}

void Protein::setChr(int chr){
    this->chr = chr;
}

void Protein::setPeptideNumber(int number){
    this->peptideNumber = number;
}

void Protein::setSpectraNumber(int number){
    this->spectraNumber = number;
}

void Protein::setMs2Quant(double quant){
    this->ms2Quant = quant;
}

void Protein::setMeanValue(double value){
    this->meanValue = value;
}

void Protein::setConfidence(double confidence){
    this->confidence = confidence;
}


QString Protein::getAccession(){
    return this->accession;
}

QString Protein::getDescription(){
    return this->description;
}

int Protein::getChr(){
    return this->chr;
}

double Protein::getCoverage(){
    return this->coverage;
}

int Protein::getPeptideNumber(){
    return this->peptideNumber;
}

int Protein::getSpectraNumber(){
    return this->spectraNumber;
}

double Protein::getMs2Quant(){
    return this->ms2Quant;
}

double Protein::getMeanValue(){
    return this->meanValue;
}

double Protein::getConfidence(){
    return this->confidence;
}

bool Protein::isChecked(){
    return this->checked;
}
