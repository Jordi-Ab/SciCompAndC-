#ifndef FORWARDEULERSOLVER_HPP
#define FORWARDEULERSOLVER_HPP

#include "AbstractODESolver.hpp"
#include <string>
#include <iostream>
class ForwardEulerSolver : public AbstractODESolver{

public:

    ForwardEulerSolver(double (*f)(double t, double y),
                       double initial_value, double final_time,
                       double step_size);
    void solve();
    double rightHandSide(double t, double y);

private:

    double (*_rhs)(double t, double y);

};

#endif // FORWARDEULERSOLVER_HPP
