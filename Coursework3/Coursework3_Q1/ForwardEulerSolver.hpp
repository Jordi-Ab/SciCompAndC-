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

    ~ForwardEulerSolver();
    void solve();
    double computeError();

private:

    ForwardEulerSolver();

    // Variable for the Initial State.
    Vector* _initial_state;

    std::string _output_file_name;
    int _save_gap;
    int _print_gap;
};

#endif // FORWARDEULERSOLVER_HPP
