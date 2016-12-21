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

    return 0;
}
