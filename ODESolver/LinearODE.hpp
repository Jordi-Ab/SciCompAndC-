#ifndef LINEARODE_HPP
#define LINEARODE_HPP

#include "ODEInterface.hpp"
#include <cmath>
class LinearODE : public ODEInterface{

public:

    LinearODE(double constant);

    // Compute right-hand side.
    void ComputeF( const double t, const Vector& u, Vector& f ) const;

    // Compute analytical solution.
    void ComputeAnalyticSolution( const double t, Vector& u ) const;

private:

    // In this case the function involves a constant
    double _my_constant;

};

#endif // LINEARODE_HPP
