#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "ChebyshevGrid1d.hpp"
#include "WaveProblem.hpp"
#include "StoermerVerletSolver.hpp"

#include "ChebyshevDifferentiationLibrary.hpp"

/*  Fills in the given Vector "u0" with values evaluated at the
 * function given in Question 4 of the Coursework for the
 * initial state*/
void setInitialState(Vector& u0, Vector* x_grid, Vector* y_grid);

/* Fills in the given Vector "v0" with zeros, because initial
 * velocity of the problem is zero.*/
void setInitialVelocity(Vector& v0, Vector* x_grid, Vector* y_grid);

int main(){

    /* Initialize all the necessary info for the problem: */
    const int Nx = 3; // Number of mesh points in the x_axis.
    const int Ny = 3; // Number of mesh points in the y_axis.
    const int c = 1; // Wave speed constant
    double t0 = 0; //   Initial Time.
    double T = 1; // Final Time
    double h = 6.0/1600; // Step Size

    // Nx+1 Gauss–Lobatto nodes in the interval [-1,1].
    ChebyshevGrid1D* x_grid = new ChebyshevGrid1D(Nx);
    // Ny+1 Gauss–Lobatto nodes in the interval [-1,1].
    ChebyshevGrid1D* y_grid = new ChebyshevGrid1D(Ny);

    /* Set Initial Conditions */
    Vector u0( (Nx+1)*(Ny+1) );
    Vector v0( (Nx+1)*(Ny+1) );

    // Set initial state according to the initial value
    // function given in the Coursework.*/
    setInitialState(u0, x_grid, y_grid);
    // Initial Velocity is a vector of zeros.
    setInitialVelocity(v0, x_grid, y_grid);

    // A folder to store the Output data (Works only in my computer), so
    // if running from another computer make sure the flag "use_complete_path"
    // is set to false.
    std::string path_data_folder = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework3/OutputData";
    bool use_complete_path = true;

    std::string output_file_name = "StormVerlet_Q4_output.dat";

    // Instantiate the wave problem given in the Coursework.
    WaveProblem Q4_rhs(c, x_grid, y_grid);

    /* Instantiate the method to be used, in this case Stoermer-Verlet,
    and provide all the necessary information for the steps.*/
    StoermerVerletSolver method(Q4_rhs, u0, v0, t0, T, h, output_file_name, 1, 1);

    method.setOutputFolder(path_data_folder);
    method.useCompletePath(use_complete_path);

    //Solve the IVP by a simple call to solve()
    method.solve();

    return 0;
}

void setInitialState(Vector& u0, Vector* x_grid, Vector* y_grid){
    int u0_ix = 0; // Index of u0.
    // Iterate through values in the x_grid.
    for(int i_x=0; i_x<x_grid->GetSize(); i_x++){
        // First iterate through all the y values to arrange
        // the vector in the Lexicographical ordering.
        for(int i_y=0; i_y<y_grid->GetSize(); i_y++){
            double x = (*x_grid)[i_x]; // x Node
            double y = (*y_grid)[i_y]; // y Node
            // Evaluate the initial condition function at the nodes.
            // and store the result in "u0".
            u0[u0_ix] = exp( -40*pow( (x-0.4),2.0 ) - 40.0*(y*y) );
            u0_ix++;
        }
    }
}

void setInitialVelocity(Vector& v0, Vector* x_grid, Vector* y_grid){
    int v0_ix = 0; // Index of v0.
    // Iterate through values in the x_grid.
    for(int i_x=0; i_x<x_grid->GetSize(); i_x++){
        // First iterate through all the y values to arrange
        // the vector in the Lexicographical ordering.
        for(int i_y=0; i_y<y_grid->GetSize(); i_y++){
            // Fill v0 with zeros.
            v0[v0_ix] = 0;
        }
    }
}


