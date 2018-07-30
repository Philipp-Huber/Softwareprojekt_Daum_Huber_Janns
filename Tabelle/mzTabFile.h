#ifndef MZTABFILE_H
#define MZTABFILE_H

#include <map>
#include <QList>
#include <QStringList>

/*!
 * \brief The mzTabFile struct
 *
 * Struct to contain data read from file and save it in a way that's relatively easy to access.
 * isValid denotes wether or not an error occurred during parsing.
 */
struct mzTabFile{
    std::map<QString, QString> metadata;
    QList<QStringList> proteins;
    QList<QStringList> peptides;
    QList<QStringList> psm;
    QList<QStringList> smallMolecules;
    bool isValid = true;
};

#endif // MZTABFILE_H
