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
    void setInitialValue(const Vector& y0);
    double getStepSize();
    double getInitialTime();
    double getFinalTime();
    Vector& getInitialValue();
    virtual void solve() = 0;
    void setOutputFolder(const std::string folder_path);
    void useCompletePath(const bool flag);

protected:

    // Pointer to the ODEObject in consideration.
    ODEInterface* _ODEObject;

    void saveSolution(const std::string file_name, const double* ts, const double* ys, int n);
    void openOutputFile(const std::string file_name);
    void writeData(double t, double y);
    void closeOutputFile();

private:

    // Variables for initial and final time
    double _final_time;
    double _initial_time;

    // Variable for the Step Size
    double _h;

    // Variable for the Initial Value.
    Vector* _initial_value;

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
