/****************************************************************************
 * This class wraps up the discretized version of the two dimensional
 * Wave Equation given in Question4 of Coursework3. Nameley:
 *
 *  u''(t) = (c^2)*L*u
 *
 * where L is a two dimensional Discretized Laplacian Operator,
 * and c is the wave speed constant.
 *
 * Laplacian operator is discretized using a Kronecker product between a Second
 * order Chebyshev Differentiation matrix, and the Identity Matrix.
 *
 *i.e. L = D2_x (x) Iy + Ix (x) D2_y
 *  # (x) -> defined as the kronecker product operand.
 *  # D2_x -> Second order Chebyshev Differentiation Matrix, defined on an x_grid
 *    of n+1 Chebyshev Gauss-Lobato nodes.
 *  # Ix -> Identity matrix with the same size as D2_x.
 *  # idem for y's
 ****************************************************************************/

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

private:

/* Important Note:
    x_grid and y_grid are vectors instead of
    ChebyshevGrid1d objects, so the object can be
    instantiated with a user defined grid,
    not limited to be a Gauss-Lobato grid.
    As ChebyshevGrid1d "is a" vector, so you can
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
    // of an interior discrete Laplace operator.
    void initInteriorLaplacian();

    // Get the interior values of a matrix.
    // i.e. Get rid of first and last columns and rows
    Matrix getInteriorValues(Matrix m);

};

#endif // WAVEPROBLEM_HPP
