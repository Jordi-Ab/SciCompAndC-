#include <iostream>
#include "ForwardEulerSolver.hpp"
#include "LinearODE.hpp"
#include <cmath>

int main(){

    // Initialize all the necessary info of the ODE problem:

    const int a = 1;            // Constant of the rhs function.
    Vector y0(1); y0[0] = 0;    // Initial Conditions.
    double t0 = 0;              // initial time.
    double T = 10;              // final time
    double h=.01;               // step size


    /* To store the Data */

    // Flag to know if program should save data on a specified folder.
    // "true" if you want to save the Data on a specific folder.
    // If "false", data will get saved either on the home directory,
    // on the working directory, or somewhere else depending on the computer or the compiler used.
    bool use_specific_folder = false;

    // A specified folder to store the Output data.
    // Modify it to be whatever you like, and set "use_specific_folder" to true.
    // # Best is to specify a folder to avoid data getting saved somewhere random.
    std::string path_data_folder = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework3/OutputData";

    // Name of the file where the solution will be stored.
    std::string output_file_name = "fwd_euler_output.dat";

    // Instantiate a Linear ODE object that contains the information of this
    // particular problem to be solved.
    LinearODE Q1_rhs(a);

    /* Instantiate the method to be used, in this case ForwardEuler,
    and provide all the necessary information for the steps.*/
    ForwardEulerSolver method(Q1_rhs, y0, t0, T, h, output_file_name, 100, 100);

    // Set the path where data will be saved.
    if (use_specific_folder) method.setOutputFolderPath(path_data_folder);

    //Solve the IVP by a simple call to solve()
    method.solve();

    /* Part2, Error Analysis: */

    // set T = 2
    method.setTimeInterval(0, 2);

    // Open a file to write the errors.
    method.openOutputFile("fwd_euler_errors.dat");
    h = 1;

    std::cout << "" << std::endl;
    std::cout << "Printing the errors." << std::endl;

    for (int i=0; h>.001; i++){
        h /= 2; // Halve the step size.
        method.setStepSize(h/2); // Change the step size in the method.
        double error = method.computeError();
        method.writeData(h, error);

        std::cout << "For h = " << h << ", error = " << error << std::endl;

    }

    method.closeOutputFile();

    std::cout << "" << std::endl;
    std::cout << "Note how every time I halve the interval, the error is roughly halved." << std::endl;
    std::cout << "This provides evidence of an O(h) convergence." << std::endl;
    std::cout << "" << std::endl;

    return 0;
}
