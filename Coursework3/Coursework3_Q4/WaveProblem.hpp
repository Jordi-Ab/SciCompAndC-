#ifndef WAVEPROBLEM_HPP
#define WAVEPROBLEM_HPP

#include "ODEInterface.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "ChebyshevDifferentiationLibrary.hpp"

class WaveProblem:public ODEInterface{

public:

    // Constructor.
    WaveProblem(const double speed,
                const Vector* x_grid,
                const Vector* y_grid);

    // Destructor.
    ~WaveProblem();

    // Compute right-hand side
    void ComputeF( const double t, const Vector& u, Vector& f )const;

    //

private:

/* Important Note:
    x_grid and y_grid are vectors instead of
    ChebyshevGrid1d objects, so the object can be
    instantiated with a user defined grid,
    not limited to be a Gauss-Lobato grid.
    As ChebyshevGrid1d "is a" vector, you can
    also use it as input.*/

    // Wave speed constant
    double _speed;

    // Nodes in the x-axis for the solution grid.
    Vector* _xgrid;

    // Nodes in the y-axis for the solution grid.
    Vector* _ygrid;

    // Interior Points of the Discrete Laplace operator.
    // (We want to solve using interior values, and after
    // that apply the Boundary conditions.)
    Matrix* _L;

    // Initialize _L instance variable with the values
    // of and interior discrete laplace operator.
    void initInteriorLaplacian();

    // Get the values that are not on boundary nodes, of a given
    // vector of states.
    Vector getInteriorValues(const Vector u) const;

    // Get the interior values of a matrix.
    // i.e. Get rid of first and last column and row
    Matrix getInteriorValues(Matrix m);


    void applyBoundaryConditions(const Vector interior_u, Vector& f) const;
};

#endif // WAVEPROBLEM_HPP
