#ifndef STOERMERVERLETSOLVER_HPP
#define STOERMERVERLETSOLVER_HPP

#include "AbstractODESolver.hpp"
#include <cmath>

class StoermerVerletSolver : public AbstractODESolver{

public:

    StoermerVerletSolver(ODEInterface& an_ODESystem,
                        const Vector& initial_state,
                        const Vector& initial_velocity,
                        const double initial_time,
                        const double final_time,
                        const double step_size,
                        const std::string output_file_name="output.dat",
                        const int save_gap=1,
                        const int print_gap=1);

    // Destructor
    ~StoermerVerletSolver();

    /*Its own print header method*/
    void printHeader();

    /*Implements Stoermer-Verlet Formula to advance one step in the state.
    The result of the step taken will get stored in the given "result vector"*/
    void advance(const double current_t, const Vector& current_state, Vector& result);

private:

    // Instance Variable that will keep track of the velocity value.
    Vector* _velocity;

};

#endif // STOERMERVERLETSOLVER_HPP
