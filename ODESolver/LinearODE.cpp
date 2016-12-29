#include "LinearODE.hpp"

LinearODE::LinearODE(double constant){
    _my_constant = constant;
}

void LinearODE::ComputeF(const double t, const Vector& u, Vector& result) const {
    result[0] = 1 / ( _my_constant + (t*t) );
}

void LinearODE::ComputeAnalyticSolution(const double t, Vector& result) const {
    result[0] = ( 1 / sqrt(_my_constant) ) * atan( t / sqrt(_my_constant) );
}
