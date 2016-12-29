#include <iostream>
#include "ForwardEulerSolver.hpp"
#include "LinearODE.hpp"
#include "OscillatorODE.hpp"
#include "StoermerVerletSolver.hpp"
#include <cmath>


void testForwardEuler();
void testStormVerlet();

int main(){

    //testForwardEuler();
    testStormVerlet();

    return 0;
}

void testForwardEuler(){

    // initialize all the necessary info of the problem:
    const int a = 1;
    Vector y0(1); y0[0] = 0; // Initial Conditions.
    double t0 = 0; // initial time.
    double T = 10; // final time
    double h=.01; // step size

    // A folder to store the Output data (Works only in my computer), so
    // if running from another computer make sure the flag "use_complete_path"
    // is set to false.
    std::string path_data_folder = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/ODESolver/Output";
    bool use_complete_path = true;

    std::string output_file_name = "fwd_euler_output.dat";

    // Instantiate a Linear ODE that contains the information of this
    // particular problem to be solved.
    LinearODE Q1_rhs(a);

    /* Instantiate the method to be used, in this case ForwardEuler,
    and provide all the necessary information for the steps.*/
    ForwardEulerSolver method(Q1_rhs,y0,t0,T,h,output_file_name,1,1);

    method.setOutputFolder(path_data_folder);
    method.useCompletePath(use_complete_path);

    //Solve the IVP by a simple call to solve()
    method.solve();

    // Part2:

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

}

void testStormVerlet(){

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
    std::string path_data_folder = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/ODESolver/Output";
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

    // Part2, Error Analysis:

    // set T = 1000
    method.setTimeInterval(0, 1000);

    // Open a file to write the errors.
    method.openOutputFile("StormVerlet_errors.dat");
    h = 1;

    std::cout << "" << std::endl;
    std::cout << "Printing the errors." << std::endl;

    double last_error = 0;
    for (int i=0; h>.001; i++){

        // Halve the step size.
        h /= 2;

        // Change the step size in the already instantiated method.
        method.setStepSize(h/2);

        // Compute Approximation error for this particular h.
        double error = method.computeError();

        // Write the result in the File.
        method.writeData(h, error);

        std::cout << "For h = " << h << ", error = " << error << std::endl;
        if (i>0){
            std::cout << "  => Error was reduced by a factor of: "<< last_error/error << std::endl;
        }
        last_error = error;

    }
    method.closeOutputFile();
}
