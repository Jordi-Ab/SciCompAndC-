/*********************************************************************
 * This class wraps up the right hand side and the Analytical Solution
 * of the problem given in Question1 of Coursework3. Nameley:
 *
 * u'(t) = 1/( a + t^2 )
 *
 * with Analytic Solution:
 *
 * u(t) = ( 1/sqrt(a) ) * atan( t/sqrt(a) )
 *
 **********************************************************************/

#ifndef LINEARODE_HPP
#define LINEARODE_HPP

#include "ODEInterface.hpp"
#include <cmath>
class LinearODE : public ODEInterface{

public:

    // Constructor
    LinearODE(double constant);

    // Compute right-hand side.
    void ComputeF( const double t, const Vector& u, Vector& f ) const;

    // Compute analytical solution.
    void ComputeAnalyticSolution( const double t, Vector& u ) const;

private:

    // In this case the function involves a constant "a"
    double _my_constant;

};

#endif // LINEARODE_HPP
