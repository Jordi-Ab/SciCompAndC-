#ifndef ABSTRACTODESOLVER_HPP
#define ABSTRACTODESOLVER_HPP

#include <stdexcept>
#include <string>
#include <fstream>
#include <iomanip>
class AbstractODESolver{

public:

    AbstractODESolver();
    //~AbstractODESolver();

    void setStepSize(double h);
    void setTimeInterval(double initial_t, double final_t);
    void setInitialValue(double y0);
    double getStepSize();
    double getInitialTime();
    double getFinalTime();
    double getInitialValue();
    virtual double rightHandSide(double y, double t) = 0;
    virtual void solve() = 0;

protected:

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
    double _initial_value;

    // Current working Directory for saving the output files:
    const std::string CWD = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/ODESolver/Output Data";

    // The above path works only in my computer, so when running on another computer this should be set to false.
    bool use_complete_output_file = true;

    // An OutputStream variable to write the soultion on a file.
    std::ofstream _output_file;

};

#endif // ABSTRACTODESOLVER_HPP
