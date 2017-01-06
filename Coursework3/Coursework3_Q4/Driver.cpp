#include <iostream>
#include <cmath>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "ChebyshevGrid1d.hpp"
#include "WaveProblem.hpp"
#include "StoermerVerletSolver.hpp"

/* Function Prototypes:*/

/*  Fills in the given Vector "u0" with values evaluated at the
 * function given in Question 4 of the Coursework for the
 * initial state*/
void setInitialState(Vector& u0, Vector* x_grid, Vector* y_grid);

/* Fills in the given Vector "v0" with zeros, because initial
 * velocity of the problem is zero.*/
void setInitialVelocity(Vector& v0, Vector* x_grid, Vector* y_grid);

/* Receives a vector, opens a file named as the given "fileName",
if it already exists, it overwrites the file with the contents of the
given vector as lines of the file. If it doesn't exists already,
it creates the file.*/
void SaveVectorToFile(Vector v, std::string fileName);

/*Main Program.*/
int main(){

    /* Initialize all the necessary info for the PDE problem: */

    const int Nx = 40;      // Number of mesh points in the x_axis.
    const int Ny = 40;      // Number of mesh points in the y_axis.
    const int c = 1;        // Wave speed constant
    double t0 = 0;          // Initial Time.
    double T = 1;           // Final Time
    double h = 6.0/1600;    // Step Size

    // Nx+1 Gauss–Lobatto nodes in the interval [-1,1].
    ChebyshevGrid1D* x_grid = new ChebyshevGrid1D(Nx);
    // Ny+1 Gauss–Lobatto nodes in the interval [-1,1].
    ChebyshevGrid1D* y_grid = new ChebyshevGrid1D(Ny);

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

    // Save the grids on a file, for plotting purposes.
    std::string xgrid_file_name = "Q4_xgrid.dat";
    std::string ygrid_file_name = "Q4_ygrid.dat";
    if (use_specific_folder){
        xgrid_file_name = path_data_folder +"/"+xgrid_file_name;
        ygrid_file_name = path_data_folder +"/"+ygrid_file_name;
    }
    SaveVectorToFile(*x_grid, xgrid_file_name);
    SaveVectorToFile(*y_grid, ygrid_file_name);

    /* Set Initial Conditions */
    Vector u0( (Nx-1)*(Ny-1) );
    Vector v0( (Nx-1)*(Ny-1) );

    // Set Initial State for Interior Grid points.
    // # According to the initial value function given in the Coursework.
    // Note, I exclude the end points because of the Boundary Conditions.
    setInitialState(u0, x_grid, y_grid);
    // Initial Velocity is a vector of zeros.
    setInitialVelocity(v0, x_grid, y_grid);

    // Instantiate the discretized version of the
    // wave problem given in the Coursework.
    WaveProblem Q4_rhs(c, x_grid, y_grid);

    // File name where the solution will get written
    std::string output_file_name = "StormVerlet_Q4_output.dat";

    /* Instantiate the method to be used, in this case Stoermer-Verlet,
    and provide all the necessary information for the steps.*/
    StoermerVerletSolver method(Q4_rhs, u0, v0, t0, T, h, output_file_name, 50, 50);

    // Set the path where data will be saved.
    if (use_specific_folder) method.setOutputFolderPath(path_data_folder);

    // Solve the IVP by a simple call to solve()
    method.solve();

    /* Note, produces the solution for the interior points.
    The boundary conditions are set when plotting.*/

    return 0;
}

void setInitialState(Vector& u0, Vector* x_grid, Vector* y_grid){
    int u0_ix = 0; // Index of u0.
    // Iterate through interior values of the x_grid.
    for(int i_x=1; i_x<x_grid->GetSize()-1; i_x++){
        // Iterate through interior values of y_grid to
        // arrange the vector in Lexicographical ordering.
        for(int i_y=1; i_y<y_grid->GetSize()-1; i_y++){
            double x = (*x_grid)[i_x]; // x Node
            double y = (*y_grid)[i_y]; // y Node
            // Evaluate the initial condition function at the nodes,
            // and store the result in "u0".
            u0[u0_ix] = exp( -40*pow( (x-0.4),2.0 ) - 40.0*(y*y) );
            u0_ix++;
        }
    }
}

void setInitialVelocity(Vector& v0, Vector* x_grid, Vector* y_grid){
    int v0_ix = 0; // Index of v0.
    // Iterate through values in the x_grid.
    for(int i_x=1; i_x<x_grid->GetSize()-1; i_x++){
        // First iterate through all the y values to arrange
        // the vector in the Lexicographical ordering.
        for(int i_y=1; i_y<y_grid->GetSize()-1; i_y++){
            // Fill v0 with zeros.
            v0[v0_ix] = 0;
        }
    }
}

void SaveVectorToFile(Vector v, std::string fileName){

    int n = v.GetSize();

    // Format output
    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(6);

    // Open file (and perform a check)
    output_file.open(fileName);
    assert(output_file.is_open());

    // Write data
    for (int i=0; i<n; i++){
        output_file << std::setw(15) << v[i] << std::endl;
    }

    // Close file
    output_file.close();

}

