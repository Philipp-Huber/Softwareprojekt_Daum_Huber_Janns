#ifndef MZPARSER_H
#define MZPARSER_H

#include <fstream>
#include <sstream>
#include <mzTabFile.h>
#include <QMessageBox>

/*!
 * \brief The mzParser class
 *
 * Singleton parser for files in mzTab format. Opens file at given path and tries to fill an mzTabFile structure with the data read.
 */
class mzParser
{
public:
    /*!
     * \brief This function returns the single instance of the parser.
     * \return The one and only instance
     */
    static mzParser& instance(){
        static mzParser _instance;
        return _instance;
    }
    ~mzParser(){}

    /*!
     * \brief This function encompasses everything this class does. Open a file at given path and read data. Fill mzTabFile structure with data.
     * Hand structure off to be handled by the loader.
     * \param path The path to the file to be read
     * \return An mzTabFile structure. mzTabFile.isValid == false in case of error
     */
    mzTabFile parse(std::string path);

private:
    /*!
     * \brief This function builds a list of column objects, i.e. a row, from a tab-separated line of text and inserts it into a list of lists, i.e. a list of rows.
     * \param iss The remaining line after the three-letter-code is removed
     * \param list The list to be inserted into
     */
    void insertRow(std::stringstream &iss, QList<QStringList> &list);

    mzParser(){}

    mzParser(const mzParser&);

    mzParser& operator = (const mzParser&);
};

#endif // MZPARSER_H
