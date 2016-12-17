#include "ForwardEulerSolver.hpp"

ForwardEulerSolver::ForwardEulerSolver(ODEInterface& an_ODESystem,
                                       const Vector& initial_value,
                                       const double initial_time,
                                       const double final_time,
                                       const double step_size,
                                       const std::string output_file_name,
                                       const int save_gap,
                                       const int print_gap){

    // Set things for AbstractODE object.
    setInitialValue(initial_value);
    setStepSize(step_size);
    setTimeInterval(initial_time, final_time);
    _ODEObject = &an_ODESystem;

    // Set things for this object.
    _output_file_name = output_file_name;
    _save_gap = save_gap;
    _print_gap = print_gap;

}

// A solver that writes the solution on an Output file at
// each time step (no need of arrays to store solution).
void ForwardEulerSolver::solve(){

    int n = getFinalTime()/getStepSize(); // Number of steps
    std::cout << "n: " << n << std::endl;
    double h = getStepSize();
    std::cout << "h: " << h << std::endl;

    //Vector derivs = _ODEObject->getDerivatives(); // Vector of u's

    openOutputFile(_output_file_name);

    Vector current_state = getInitialValue();
    Vector next_state(current_state);
    double current_t = getInitialTime();

    while(current_t < getFinalTime()){

        writeData(current_t, current_state[0]); // Which data you want, the one at 0?
        double next_t = current_t + h;
        std::cout << "  next_t: " << next_t << std::endl;

        // Evaluate right hand side function at current time, current state,
        // store the result in next state.
        _ODEObject->ComputeF(current_t, current_state, next_state);

        next_state = current_state + next_state*h; // Fwd Euler formula.
        std::cout << "  next_y: " << next_state << std::endl;

        current_t = next_t; // Take one step in time.
        current_state = next_state; // Take one step in the state.

    }

    closeOutputFile();

}




