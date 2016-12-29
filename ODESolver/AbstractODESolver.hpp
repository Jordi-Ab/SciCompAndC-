#ifndef ABSTRACTODESOLVER_HPP
#define ABSTRACTODESOLVER_HPP

#include <stdexcept>
#include <string>
#include <fstream>
#include <iomanip>
#include "ODEInterface.hpp"
class AbstractODESolver{

public:

    // Destructor
    ~AbstractODESolver();

    /* Setters and Getters let the instance variables be private instead of protected.
     * I prefer it this way because then you can change subtlties of the problem from
     * the Driver file without the need of instantiating a new problem.*/
    void setStepSize(double h);
    void setTimeInterval(double initial_t, double final_t);
    void setInitialState(const Vector& initial_state);
    double getStepSize();
    double getInitialTime();
    double getFinalTime();
    Vector getInitialState();

    /*
     * Note about Solve:
     * In the Question sheet, we are asked to declare it as pure virtual.
     * I prefered leaving solve inside this class, and instead
     * make "advance" a pure virtual method, which is what changes between
     * different steppers for IVP's
     */
    void solve();
    double computeError();

    void setOutputFolder(const std::string folder_path);
    void useCompletePath(const bool flag);
    void openOutputFile(const std::string file_name);
    void closeOutputFile();
    void writeData(const double t, const Vector& us);
    void writeData(const double h, double e);

protected:

    // Pointer to the ODE Object in consideration.
    ODEInterface* _ODEObject;

    std::string _output_file_name;
    int _save_gap;
    int _print_gap;

    // These are the virtual methods that will get overriden on each different stepper.
    virtual void printHeader() = 0;
    virtual void advance(const double current_t, const Vector& current_state, Vector& result) = 0;

private:

    // Variables for initial and final time
    double _final_time;
    double _initial_time;

    // Variable for the Step Size
    double _h;


    /* Variable for Initial State
     *  All IVP's have an initial state, so this variable can lay
     *  on the AbstractODE Solver.*/
    Vector* _initial_state;

    // An OutputStream variable to write the soultion on a file.
    std::ofstream _output_file;

    // Current working Directory for saving the output files:
    // Set to the home directory by default
    std::string CWD = "/Users/user/";

    // The above path works only in my computer,
    // so when running on another computer this should be set to false.
    bool _use_complete_output_file = false; // false by default

    void printData(const double t, const Vector& us);

    // Default Constructor.
    //AbstractODESolver();

};

#endif // ABSTRACTODESOLVER_HPP
