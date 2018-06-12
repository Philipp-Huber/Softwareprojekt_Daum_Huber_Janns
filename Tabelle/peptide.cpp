#include "peptide.h"

Peptide::Peptide(QObject *parent) :
    QObject(parent)
{

}

void Peptide::updateDisplayed(bool displayed){
    setDisplayed(displayed);
}



//getter und setter
void Peptide::setDisplayed(bool displayed){
    this->displayed = displayed;
    // force Model to update
}

void Peptide::setChecked(bool checked){
    this->checked = checked;
}

void Peptide::setConfidence(double confidence){
    this->confidence = confidence;
}

void Peptide::setSpectraNumber(int number){
    this->spectraNumber = number;
}

void Peptide::setStart(int start){
    this->start = start;
}

void Peptide::setSequence(QString seq){
    this->sequence = seq;
}

void Peptide::setPl(int pl){
    this->pl = pl;
}

int Peptide::getPl(){
    return pl;
}

QString Peptide::getSequence(){
    return sequence;
}

int Peptide::getStart(){
    return start;
}

int Peptide::getSpectraNumber(){
    return spectraNumber;
}

double Peptide::getConfidence(){
    return confidence;
}

bool Peptide::isChecked(){
    return checked;
}

bool Peptide::isDisplayed(){
    return displayed;
}

