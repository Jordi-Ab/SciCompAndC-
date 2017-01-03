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

    ~StoermerVerletSolver();

    void solve();
    double computeError();

private:

    // Variable for the Initial State.
    Vector* _initial_state;

    // Variable for the Initial Velocity.
    Vector* _initial_velocity;

    std::string _output_file_name;
    int _save_gap;
    int _print_gap;


};

#endif // STOERMERVERLETSOLVER_HPP
