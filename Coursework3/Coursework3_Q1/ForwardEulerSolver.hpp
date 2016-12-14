#ifndef FORWARDEULERSOLVER_HPP
#define FORWARDEULERSOLVER_HPP

#include "AbstractODESolver.hpp"
#include "LinearODE.hpp"
class ForwardEulerSolver: public AbstractODESolver{

public:

    // Constructor for a System of ODEs
    ForwardEulerSolver(ODEInterface& an_ODESystem,
                       const Vector&initial_state,
                       const double initial_time,
                       const double final_time,
                       const double step_size,
                       const std::string output_file_name="output.dat",
                       int saveGap = 1,
                       int printGap = 1);

    // Constructor for a Linear ODE
    ForwardEulerSolver(LinearODE& an_ODE,
                       const double initial_state,
                       const double initial_time,
                       const double final_time,
                       const double step_size,
                       const std::string output_file_name="output.dat",
                       int saveGap = 1,
                       int printGap = 1);

    void solve();

};

#endif // FORWARDEULERSOLVER_HPP
