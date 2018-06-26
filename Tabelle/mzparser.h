#ifndef MZPARSER_H
#define MZPARSER_H

#include <stdio.h>
#include <map>
#include <list>

//Singleton Parser for files in mzTab format
class mzParser
{
public:
    static mzParser& instance(){
        static mzParser _instance;
        return _instance;
    }
    ~mzParser(){}

    mzTabFile parse(std::string path);

private:
    mzParser(){}

    mzParser(const mzParser&);

    mzParser& operator = (const mzParser&);
};

//Struct to contain data read from the file and save it in a relatively easy to access way
struct mzTabFile{
    std::map<std::string, std::string> metadata;
    std::list<std::list<std::string>> proteins;
    std::list<std::list<std::string>> peptides;
    std::list<std::list<std::string>> psm;
    std::list<std::list<std::string>> smallMolecules;
};

#endif // MZPARSER_H
