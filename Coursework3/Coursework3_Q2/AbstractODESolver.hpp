#ifndef ABSTRACTODESOLVER_HPP
#define ABSTRACTODESOLVER_HPP

#include <stdexcept>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "ODEInterface.hpp"
class AbstractODESolver{

public:

    /* Note:
     * Setters and Getters let the instance variables be private instead of protected.
     * I prefer it this way because then you can change subtlties of the problem from
     * the Driver file without the need of instantiating a new object.*/

    // Sets the step size of the ODE problem to the given number.
    void setStepSize(double h);

    // Sets the initial time and final time of the ODE problem
    void setTimeInterval(double initial_t, double final_t);

    // Returns the current step size.
    double getStepSize();

    // Returns the initial time.
    double getInitialTime();

    // Returns the final time.
    double getFinalTime();

    // Changes the Path of the Output folder where the solution file will be saved.
    void setOutputFolderPath(const std::string folder_path);

    /* Writes Data on the "output file" instance variable,
    * row-wise, per time unit, and column wise for Vector components.
    * i.e. First column of the row is the time variable "t", second column
    * is the first component inside the Vector "us", and so on for the
    * rest of the components.
    * Ex:
    *   t   component1  component2  ...     component_n
    *   -----------------------------------------------
    *   0   us[0]       us[1]       ...     us[n]
    *   1   us[0]       us[1]       ...     us[n]
    *   .
    *   .
    *   .
    *   n   us[0]       us[1]       ...     us[n]
    */
    void writeData(const double t, const Vector& us);

    /* Used to write the errors on a file.
     * Writes Data on the "output file" instance variable,
    * row-wise, per time unit, and column wise for the error value.
    * i.e. First column of the row is the time variable "t", second column
    * is the error value at that time.
    * Ex:
    *   t   error
    *   ---------
    *   0   e0
    *   1   e1
    *   .
    *   .
    *   .
    *   n   en
    */
    void writeData(const double h, double e);

    // Opens the "output file" instance variable, with the given name.
    void openOutputFile(const std::string file_name);

    // Closes the "output file" instance variable
    void closeOutputFile();

    // Solve method. Will be overwritten depending on the method used.
    virtual void solve() = 0;

protected:

    /*Variables and functions that can be used by inherited classes.*/

    // Pointer to the ODE Object in consideration.
    ODEInterface* _ODEObject;

    // Prints a header before printing the result on the Console Window
    void printHeader(const std::string class_name);

    /*
     * Prints the given Vector of state "us" at the given time,
     * on the Console Window.
     * Vector of states "us" will have as many components as equations
     * there are on the system, so the method will just print a maximum
     * of 3 components to avoid console window cluttering.
    */
    void printData(const double t, const Vector& us);

private:

    // Variables for the time interval.
    double _final_time;
    double _initial_time;

    // Variable for the Step Size
    double _h;

    // An OutputStream variable to write the soultion on a file.
    std::ofstream _output_file;

    // Complete Path for saving the output files:
    // Set to the home directory by default on some computers.
    // Set to the current working directory by default on other computers.
    std::string _output_folder_path = ""; // Empty by default.

    // Boolean instance variable to know if the output file should be saved on
    // a folder specified by the user.
    bool _use_complete_output_file = false; // false by default

};

#endif // ABSTRACTODESOLVER_HPP
