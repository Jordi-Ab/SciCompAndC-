#ifndef ABSTRACTODESOLVER_HPP
#define ABSTRACTODESOLVER_HPP

#include <stdexcept>
#include <string>
#include <fstream>
#include <iomanip>
#include "ODEInterface.hpp"
class AbstractODESolver{

public:

    //AbstractODESolver();
    //~AbstractODESolver();

    /* Setters and Getters let the instance variables be private instead of protected.
     * I prefer it this way because then you can change subtlties of the problem from
     * the Driver file.*/
    void setStepSize(double h);
    void setTimeInterval(double initial_t, double final_t);
    double getStepSize();
    double getInitialTime();
    double getFinalTime();

    virtual void solve() = 0;

    void setOutputFolder(const std::string folder_path);
    void useCompletePath(const bool flag);
    void writeData(const double t, const Vector& us);
    void writeData(const double h, double e);
    void openOutputFile(const std::string file_name);
    void closeOutputFile();

protected:

    // Pointer to the ODE Object in consideration.
    ODEInterface* _ODEObject;

    void printHeader(const std::string class_name);
    void printData(const double t, const Vector& us);

private:

    // Variables for initial and final time
    double _final_time;
    double _initial_time;

    // Variable for the Step Size
    double _h;

    // An OutputStream variable to write the soultion on a file.
    std::ofstream _output_file;

    // Current working Directory for saving the output files:
    // Set to the home directory by default
    std::string CWD = "/Users/user/";

    // The above path works only in my computer,
    // so when running on another computer this should be set to false.
    bool _use_complete_output_file = false; // false by default

};

#endif // ABSTRACTODESOLVER_HPP
