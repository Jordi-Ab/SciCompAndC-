#include "StoermerVerletSolver.hpp"

StoermerVerletSolver::StoermerVerletSolver( ODEInterface& an_ODESystem,
                                            const Vector& initial_state,
                                            const Vector& initial_velocity,
                                            const double initial_time,
                                            const double final_time,
                                            const double step_size,
                                            const std::string output_file_name,
                                            const int save_gap,
                                            const int print_gap){

    // Set things for AbstractODE object.
    setStepSize(step_size);
    setTimeInterval(initial_time, final_time);
    setInitialState(initial_state);

    _ODEObject = &an_ODESystem;
    _output_file_name = output_file_name;

    if (save_gap <= 0) _save_gap = 1;
    else if (save_gap >= final_time/step_size) _save_gap = final_time;
    else _save_gap = save_gap;

    if (print_gap <= 0) _print_gap = 1;
    else if (print_gap >= final_time/step_size) _print_gap = final_time;
    else _print_gap = print_gap;

    // Initialize Velocity instance
    _velocity = new Vector(initial_velocity);
}

StoermerVerletSolver::~StoermerVerletSolver(){
    delete _velocity;
}

void StoermerVerletSolver::advance(const double current_t, const Vector& current_state, Vector& result){

    double h = getStepSize();
    Vector current_vel = *_velocity;
    Vector next_vel(current_vel);

    // Evaluate on rhs (right hand side).
    _ODEObject->ComputeF(current_t, current_state, result);

    // Apply Stoermer-Verlet Formula.

    next_vel = current_vel + result*h;
    result = current_state + next_vel*h; // Result gets overwritten to hold the result of the next state.

    // Overwrite the velocity instance with the obtained velocity value
    *_velocity = next_vel;
}

/*void StoermerVerletSolver::advance(const double current_t, const Vector& current_state, Vector& result){

    double h = getStepSize();
    Vector current_vel = *_velocity;
    Vector next_vel(current_vel);

    Vector next_state(current_state);
    Vector f1(result);
    Vector f2(result);

    // Evaluate on rhs (right hand side).
    _ODEObject->ComputeF(current_t, current_state, f1);
    next_state = current_state + ( current_vel + f1*(h/2) )*h;

    _ODEObject->ComputeF(current_t, next_state, f2);
    next_vel = current_vel + f1*(h/2) + f2*(h/2);

    result = next_state; // Result gets overwritten to hold the result of the next state.

    // Overwrite the velocity instance with the obtained velocity value
    *_velocity = next_vel;
}*/

void StoermerVerletSolver::printHeader(){
    std::cout << "" << std::endl;
    std::cout << "Approximating solution using Stoermer-Verlet Method." << std::endl;
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
