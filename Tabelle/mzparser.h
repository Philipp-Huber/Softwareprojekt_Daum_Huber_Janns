#ifndef MZPARSER_H
#define MZPARSER_H

#include <fstream>
#include <sstream>
#include <mzTabFile.h>

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
    void insertRow(std::stringstream &iss, QList<QStringList> &list);

    mzParser(){}

    mzParser(const mzParser&);

    mzParser& operator = (const mzParser&);
};

#endif // MZPARSER_H
