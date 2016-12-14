#ifndef LINEARODE_HPP
#define LINEARODE_HPP

#include "ODEInterface.hpp"
class LinearODE : public ODEInterface{

public:

    LinearODE();

    // Compute right-hand side (pure virtual)
    void ComputeF( const double t, const Vector& u, Vector& f ) const = 0;

    // Compute analytical solution
    void ComputeAnalyticSolution( const double t, Vector& u ) const;

private:

    // Variable for the right hand side function.
    double (*_rhs)(double, double);

    // Variable for the true solution function.
    double (*_true_sol)(double, double);

};

#endif // LINEARODE_HPP
