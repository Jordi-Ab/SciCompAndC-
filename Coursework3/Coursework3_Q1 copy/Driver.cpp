#include <iostream>
#include "ForwardEulerSolver.hpp"
#include "LinearODE.hpp"
#include <cmath>

int main(){

    // initialize all the necessary info of the problem:
    const int a = 1;
    Vector y0(1); y0[0] = 0; // Initial Conditions.
    double t0 = 0; // initial time.
    double T = 10; // final time
    double h=.01; // step size

    // A folder to store the Output data (Works only in my computer), so
    // if running from another computer make sure the flag "use_complete_path"
    // is set to false.
    std::string path_data_folder = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework3/OutputData";
    bool use_complete_path = true;

    std::string output_file_name = "fwd_euler_output.dat";

    // Instantiate a Linear ODE that contains the information of this
    // particular problem to be solved.
    LinearODE Q1_rhs(a);

    /* Instantiate the method to be used, in this case ForwardEuler,
    and provide all the necessary information for the steps.*/
    ForwardEulerSolver method(Q1_rhs,y0,t0,T,h,output_file_name,1,1);

    //method.setOutputFolder(path_data_folder);
    //method.useCompletePath(use_complete_path);

    //Solve the IVP by a simple call to solve()
    method.solve();

    /*
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
    std::cout << "" << std::endl;*/

    return 0;
}
