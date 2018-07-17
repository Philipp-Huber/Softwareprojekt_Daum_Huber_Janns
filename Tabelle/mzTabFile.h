#ifndef MZTABFILE_H
#define MZTABFILE_H

#include <map>
#include <QList>
#include <QStringList>

//Struct to contain data read from file and save it in a way that's relatively easy to access
struct mzTabFile{
    std::map<QString, QString> metadata;
    QList<QStringList> proteins;
    QList<QStringList> peptides;
    QList<QStringList> psm;
    QList<QStringList> smallMolecules;
    bool isValid = true;
};

#endif // MZTABFILE_H
