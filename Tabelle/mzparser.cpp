#include "mzparser.h"

//mzTabFile specification:
//5 sections: Metadata, Proteins, Peptides, PSM data, small molecules
//Every section except metadata optional!
//Each line preceded by three-letter code to identify content:
//MTD: Metadata
//PRH: Protein column headers
//PRT: Protein row data
//PEH: Peptide column headers
//PEP: Peptide row data
//PSH: PSM column headers
//PSM: PSM row data
//SMH: Small Molecule column headers
//SML: Small Molecule row data
mzTabFile mzParser::parse(std::string path){
    std::ifstream readFile(path);
    mzTabFile data;
    std::string line;

    //Get each line in the file individually and store it as a string
    while(std::getline(readFile, line)){
        //Convert string into stringstream
        std::stringstream iss(line);
        std::string code;

        //Get everything in the stringstream up to the first tab and store it, this should be the three-letter code
        std::getline(iss, code, '\t');
        //Look at the three-letter code and decide what to do
        if(code == "MTD"){
            //Metadata are key-value pairs, so we store them in a map
            std::string key;
            std::string value;
            std::getline(iss, key, '\t');
            std::getline(iss, value);
            data.metadata.insert(std::pair<QString, QString>(QString::fromStdString(key), QString::fromStdString(value)));
        } else if(code == "PRH" || code == "PRT"){
            insertRow(iss, data.proteins);
        } else if(code == "PEH" || code == "PEP"){
            insertRow(iss, data.peptides);
        } else if(code == "PSH" || code == "PSM"){
            insertRow(iss, data.psm);
        } else if(code == "SMH" || code == "SML"){
            insertRow(iss, data.smallMolecules);
        } else if(code == "COM" || code.size() == 0 || code.size() == 1){
            //Do nothing, since they're comments or empty lines
            //(for some reason, empty lines sometimes count as size 0 and sometimes as size 1, apparently)
        } else {
            //If its none of the above, shenanigans are afoot
            QMessageBox::information(NULL, "Incompatible File", "Header data corrupt or not a valid file.\nLast read: " + QString::fromStdString(code));
            data.isValid = false;
            return data;
        }
    }

    return data;
}

//Helper function, gets the stringstream and current list to fill
void mzParser::insertRow(std::stringstream &iss, QList<QStringList> &list){
    std::string element;
    QStringList row;
    //Get each element from the stringstream separated by tab and append them to the new row list
    while(std::getline(iss, element, '\t')){
        row.append(QString::fromStdString(element).trimmed());
    }
    //Append the row to the list given as parameter => Now we got a list of rows that are a list of column items
    list.append(row);
}
