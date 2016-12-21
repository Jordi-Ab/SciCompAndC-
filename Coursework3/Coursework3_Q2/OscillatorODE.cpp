#include "OscillatorODE.hpp"


OscillatorODE::OscillatorODE(double constant){
    _a = constant;
}

void OscillatorODE::ComputeF(const double t, const Vector& u, Vector& result) const {
    double c = -(_a*_a);
    // We know that on this particular problem we are working with
    // a single second order ODE, not a system, so we can work with the
    // components at zero.
    result[0] = u.Read(0)*c + sin(2*t);
}

void OscillatorODE::ComputeAnalyticSolution(const double t, Vector& result) const {
    double gamma = _a*((_a*_a) - 4);
    result[0] = ( gamma*cos(_a*t) + _a*sin(2*t) - 2*sin(_a*t) ) / gamma;
}

