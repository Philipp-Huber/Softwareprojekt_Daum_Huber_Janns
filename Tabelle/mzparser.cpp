#include "mzparser.h"

mzParser::mzParser()
{
}

//mzTabFile specification:
//5 sections: Metadata, Proteins, Peptides, PSM data, small molecules
//Every section except metadata optional!
//Each line preceded by three letter code to identify content:
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

    while(std::getline(readFile, line)){
        std::stringstream iss(line);
        std::string code;

        std::getline(iss, code, '\t');
        switch(code){
        case 'MTD':
            std::string key;
            std::string value;
            std::getline(iss, key, '\t');
            std::getline(iss, value);
            data.metadata.insert(std::pair<std::string, std::string>(key, value));
            break;
        case 'PRH':
        case 'PRT':
            insertRow(iss, data.proteins);
            break;
        case 'PEH':
        case 'PEP':
            insertRow(iss, data.peptides);
            break;
        case 'PSH':
        case 'PSM':
            insertRow(iss, data.psm);
        case 'SMH':
        case 'SML':
            insertRow(iss, data.smallMolecules);
            break;
        default:

            break;
        }
    }

    return data;
}

void mzParser::insertRow(std::stringstream &iss, std::list<std::string> &list){
    std::string element;
    std::list<std::string> row;
    while(std::getline(iss, element, '\t')){
        row.push_back(element);
    }
    list.push_back(row);
}
