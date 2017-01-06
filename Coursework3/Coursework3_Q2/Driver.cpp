#include <iostream>
#include "OscillatorODE.hpp"
#include "StoermerVerletSolver.hpp"
#include "Vector.hpp"

int main(){

    // Initialize all the necessary info for the problem:

    const int a = 1;            // Constant of the rhs function.
    Vector u0(1); u0[0] = 1;    // Initial State.
    Vector v0(1); v0[0] = 0;    // Initial Velocity
    double t0 = 0;              // Initial Time.
    double T = 20;              // Final Time
    double h=.01;               // Step Size

    /* To store the Data */

    // Flag to know if program should save data on a specified folder.
    // "true" if you want to save the Data on a specific folder.
    // If "false", data will get saved either on the home directory,
    // on the working directory, or somewhere else depending on the computer or the compiler used.
    bool use_specific_folder = true;

    // A specified folder to store the Output data.
    // Modify it to be whatever you like, and set "use_specific_folder" to true.
    // # Best is to specify a folder to avoid data getting saved somewhere random.
    std::string path_data_folder = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework3/OutputData";

    std::string output_file_name = "StormVerlet_output.dat";

    // Instantiate an OscillatorODE that contains the information of this
    // particular problem to be solved.
    OscillatorODE Q2_rhs(a);

    /* Instantiate the method to be used, in this case Stoermer-Verlet,
    and provide all the necessary information for the steps.*/
    StoermerVerletSolver method(Q2_rhs, u0, v0, t0, T, h, output_file_name, 1, 100);

    // Set the path where data will be saved.
    if (use_specific_folder) method.setOutputFolderPath(path_data_folder);

    //Solve the IVP by a simple call to solve()
    method.solve();

    /* Part2, Error Analysis: */

    // set T = 1000
    method.setTimeInterval(0, 1000);

    h = 1;

    std::cout << "" << std::endl;
    std::cout << "Error Analysis:" << std::endl;

    // Open a file to write the errors.
    method.openOutputFile("StormVerlet_errors.dat");

    for (int i=0; h>.001; i++){
        h /= 2; // Halve the step size.
        method.setStepSize(h/2); // Change the step size in the method.
        double error = method.computeError();
        method.writeData(h, error);

        std::cout << "For h = " << h << ", error = " << error << std::endl;
    }

    method.closeOutputFile();

    std::cout << "" << std::endl;
    std::cout << "Note how every time I halve the interval, the error is roughly";
    std::cout << " reduced by a factor of 4 at the beginning, and by smaller factors";
    std::cout << " as h reduces further." << std::endl;
    std::cout << "This provides evidence of an O(h^2) convergence." << std::endl;
    std::cout << "" << std::endl;

    return 0;
}
