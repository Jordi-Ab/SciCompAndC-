#ifndef FORWARDEULERSOLVER_HPP
#define FORWARDEULERSOLVER_HPP

#include "AbstractODESolver.hpp"
#include <string>
#include <iostream>
class ForwardEulerSolver : public AbstractODESolver{

public:

    ForwardEulerSolver(ODEInterface& an_ODESystem,
                       const Vector& initial_value,
                       const double initial_time,
                       const double final_time,
                       const double step_size,
                       const std::string output_file_name = "output.dat",
                       const int save_gap = 1,
                       const int print_gap = 1);


    /*Its own print header method*/
    void printHeader();

    /*Implements Forward Euler Formula to advance one step.
    The result of the step taken will get stored in the given "result vector"*/
    void advance(const double current_t, const Vector& current_state, Vector& result);


private:

    ForwardEulerSolver();

};

#endif // FORWARDEULERSOLVER_HPP
