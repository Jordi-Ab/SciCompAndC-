#include "ForwardEulerSolver.hpp"

// Constructor for a System of Linear ODE's
ForwardEulerSolver::ForwardEulerSolver(ODEInterface& an_ODESystem,
                                       const Vector&initial_state,
                                       const double initial_time,
                                       const double final_time,
                                       const double step_size,
                                       const std::string output_file_name="output.dat",
                                       int saveGap = 1,
                                       int printGap = 1){
    setInitialValue(initial_state);
    setTimeInterval(initial_time, final_time);
    setStepSize(step_size);

}

// Constructor for a Single Linear ODE's
ForwardEulerSolver::ForwardEulerSolver(LinearODE& an_ODE,
                                       const double initial_state,
                                       const double initial_time,
                                       const double final_time,
                                       const double step_size,
                                       const std::string output_file_name="output.dat",
                                       int saveGap = 1,
                                       int printGap = 1){
    setInitialValue(initial_state);
    setTimeInterval(initial_time, final_time);
    setStepSize(step_size);

}

void solve(){

}
