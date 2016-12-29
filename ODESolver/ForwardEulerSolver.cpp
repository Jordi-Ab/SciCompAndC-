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
        // Private Instances
    setStepSize(step_size);
    setInitialState(initial_value);
    setTimeInterval(initial_time, final_time);

        // Protected Instances
    _ODEObject = &an_ODESystem;
    _output_file_name = output_file_name;

    if (save_gap <= 0) _save_gap = 1;
    else if (save_gap >= final_time/step_size) _save_gap = final_time;
    else _save_gap = save_gap;

    if (print_gap <= 0) _print_gap = 1;
    else if (print_gap >= final_time/step_size) _print_gap = final_time;
    else _print_gap = print_gap;

}

void ForwardEulerSolver::advance(const double current_t, const Vector& current_state, Vector& result){
    double h = getStepSize();

    /*Evaluate right hand side at current_time and current_state.
    Store the result in "result" vector.*/
    _ODEObject->ComputeF(current_t, current_state, result);

    /*Overwrite "result" vector with the result of Forward Euler formula*/
    result = current_state + result*h;
}

void ForwardEulerSolver::printHeader(){
    std::cout << "" << std::endl;
    std::cout << "Approximating solution using Forward Euler Method." << std::endl;
    std::cout << "" << std::endl;
    std::cout << "  Initial Time: " << getInitialTime() << std::endl;
    std::cout << "  Final Time: " << getFinalTime() << std::endl;
    std::cout << "  Step Size: " << getStepSize() << std::endl;
    std::cout << "  Number of Steps: " << getFinalTime()/getStepSize() << std::endl;

    if (getInitialState().GetSize() > 3){
        std::cout << "# Note: Will just print the first 3 components of the ";
        std::cout << "solutions vector on screen." << std::endl;
    }
    std::cout << "" << std::endl;
}





