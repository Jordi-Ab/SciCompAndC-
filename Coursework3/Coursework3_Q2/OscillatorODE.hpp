/****************************************************************************
 * This class wraps up the right hand side and the Analytical Solution
 * of the problem given in Question2 of Coursework3. Nameley:
 *
 *  u''(t) = -a*u + sin(2*t)
 *
 * with AnalyticalSolution:
 *  u(t) = ( a(a^2 - 4)*cos(4*t) + a*sin(2*t) - 2*sin(a*t) ) / ( a(a^2 - 4) );
 *
 * a is a constant which is defined here as an instance variable,
 * and should be provided by the user when instantianting this object.
 ****************************************************************************/

#ifndef OSCILLATORODE_HPP
#define OSCILLATORODE_HPP

#include <cmath>
#include "Vector.hpp"
#include "ODEInterface.hpp"

class OscillatorODE : public ODEInterface{

public:

    OscillatorODE(double constant);

    // Evaluate rhs function at time "t", state (vector) u,
    // and store the result in "result vector."
    void ComputeF(const double t, const Vector& u, Vector& result) const;

    // Evaluate Analytical solution function at time "t", and
    // store the result in "result vector."
    void ComputeAnalyticSolution(const double t, Vector& result) const;

private:

    // Constant ("a") used by right hand side function
    // and Analytic Solution.
    double _a;

};

#endif // OSCILLATORODE_HPP
