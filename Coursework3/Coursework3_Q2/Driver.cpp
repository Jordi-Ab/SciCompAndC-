#include <iostream>
#include "OscillatorODE.hpp"
#include "StoermerVerletSolver.hpp"
#include "Vector.hpp"

int main(){


    // Initialize all the necessary info for the problem:
    const int a = 1;
    Vector u0(1); u0[0] = 1; // Initial State.
    Vector v0(1); v0[0] = 0; // Initial Velocity
    double t0 = 0; //   Initial Time.
    double T = 20; // Final Time
    double h=.01; // Step Size

    // A folder to store the Output data (Works only in my computer), so
    // if running from another computer make sure the flag "use_complete_path"
    // is set to false.
    std::string path_data_folder = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework3/OutputData";
    bool use_complete_path = true;

    std::string output_file_name = "StormVerlet_output.dat";

    // Instantiate an OscillatorODE that contains the information of this
    // particular problem to be solved.
    OscillatorODE Q2_rhs(a);

    /* Instantiate the method to be used, in this case Stoermer-Verlet,
    and provide all the necessary information for the steps.*/
    StoermerVerletSolver method(Q2_rhs, u0, v0, t0, T, h, output_file_name);

    method.setOutputFolder(path_data_folder);
    method.useCompletePath(use_complete_path);

    //Solve the IVP by a simple call to solve()
    method.solve();

    // Part2:

    // set T = 1000
    method.setTimeInterval(0, 1000);

    // Open a file to write the errors.
    method.openOutputFile("StormVerlet_errors.dat");
    h = 1;

    std::cout << "" << std::endl;
    std::cout << "Printing the errors." << std::endl;

    double last_error = 0;
    for (int i=0; h>.001; i++){

        h /= 2; // Halve the step size.
        method.setStepSize(h/2); // Change the step size in the method.
        double error = method.computeError();

        if (i>0){
            std::cout << "For h = " << h << ", error = " << error << std::endl;
            method.writeData(h, error);
            std::cout << "  => Error was reduced by a factor of: "<< last_error/error << std::endl;
        }
        last_error = error;


    }
    

    return 0;
}
