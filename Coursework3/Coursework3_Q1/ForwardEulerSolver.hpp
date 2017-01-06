/******************************************************************
 * Forward Euler method for solving Initial Value problems,
 * for systems of First Order ODE's,
 *
 * Of the form:
 *
 * u'(t) = f(t, u) on the interval t = [t0, T]
 * with:
 *  u(0) = u0
 *
 * # u0 is the initial state,
 * # t0 is the initial time,
 * # T is the final time, and
 * # f(t, u) is the right hand side function defined as a
 *   LinearODE object. (t is the time variable, u is
 *   the Vector of states).
 *****************************************************************/

#ifndef FORWARDEULERSOLVER_HPP
#define FORWARDEULERSOLVER_HPP

#include "AbstractODESolver.hpp"
#include "Vector.hpp"
#include <string>
#include <iostream>
class ForwardEulerSolver : public AbstractODESolver{

public:

    // Specialized Constructor
    ForwardEulerSolver(ODEInterface& an_ODESystem,
                       const Vector& initial_value,
                       const double initial_time,
                       const double final_time,
                       const double step_size,
                       const std::string output_file_name = "output.dat",
                       const int save_gap = 1,
                       const int print_gap = 1);

    // Destructor
    ~ForwardEulerSolver();

    // Overwrites the "solve" method in "AbstractODESolver".
    // Approximates the solution at each time step using
    // Forward Euler Formula, and writes the approximation
    // at each time step on an output folder.
    void solve();

    // Returns the maximum norm of the difference between the
    // computed and the true solution, of all time steps.
    double computeError();

private:

    // Variable for the Initial State.
    Vector* _initial_state;

    // Name of the file where the approximate solution at each time step
    // will be written.
    std::string _output_file_name;

    /*
     * Time step gap at which you want to save the data.
     * Ex:
     *
     * Gap of one will save the data at every time step.
     * Gap of two will save the data at every two time steps.
     * A gap that equals the number of steps to be taken,
     * will save the data at the first time step (t=t0),
     * and at the last time step (t=T).
     */
    int _save_gap;

    /*
     * Time step gap at which you want to print the data.
     * Ex:
     *
     * Gap of one will print the data at every time step.
     * Gap of two will print the data at every two time steps.
     * A gap that equals the number of steps to be taken,
     * will print the data at the first time step (t=t0),
     * and at the last time step (t=T).
     */
    int _print_gap;
};

#endif // FORWARDEULERSOLVER_HPP
