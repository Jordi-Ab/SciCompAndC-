#ifndef ABSTRACTODESOLVER_HPP
#define ABSTRACTODESOLVER_HPP

#include "ODEInterface.hpp"

class AbstractODESolver{

public:

    AbstractODESolver();

    void setStepSize(double h);
    void setTimeInterval(double initial_t, double final_t);
    void setInitialValue(double y0);
    void setRHS(double (*RHS)(double, double));
    double getStepSize();
    double getInitialTime();
    double getFinalTime();
    double getInitialValue();
    //virtual double rightHandSide(double y, double t) = 0;
    virtual void solve() = 0;
    virtual ~AbstractODESolver();

protected:

    // Variables for initial and final time
    double _final_time;
    double _initial_time;

    // Pointer for the ODE System in consideration
    ODEInterface* _ODE_system;

    // Variable for the Step Size
    double _h;


    // Variable for the Initial Value.
    double _initial_value;

private:

    // Current working Directory for saving the output files:
    const std::string CWD = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework3/OutputData";

    // The above path works only in my computer, so when running on another computer this should be set to false.
    bool use_complete_output_file = true;


};

#endif // ABSTRACTODESOLVER_HPP
