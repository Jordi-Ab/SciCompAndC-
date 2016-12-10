#ifndef SAVETOFILES_HPP
#define SAVETOFILES_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <assert.h>
class saveToFiles{

public:

    saveToFiles();
    saveToFiles(std::string path_name, std::string file_name);

    std::string getPathName() const;
    std::string getFileName() const;
    std::string getFilePath() const;

    void setPathName(std::string path_name);
    void setFileName(std::string file_name);

    void saveVectorToFile(int n, double* v);
    void saveVectorsToFileAsColumns(double** vectors, int n_cols, int vector_size);

private:

    //INSTANCE VARIABLES
    std::string path_name;
    std::string file_name;

};

#endif // SAVETOFILES_HPP
