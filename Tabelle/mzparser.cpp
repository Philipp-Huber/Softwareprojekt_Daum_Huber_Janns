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
        std::stringstream iss;
        std::string code;

        std::getline(iss, code, '\t');
        switch(code){
        case 'MTD':

            break;
        case 'PRH':

            break;
        case 'PRT':

            break;
        case 'PEH':

            break;
        case 'PEP':

            break;
        case 'PSH':

            break;
        case 'PSM':

            break;
        case 'SMH':

            break;
        case 'SML':

            break;
        default:

            break;
        }
    }
}
