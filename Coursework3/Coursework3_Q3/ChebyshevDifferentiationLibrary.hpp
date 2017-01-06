#ifndef CHEBYSHEVDIFFERENTIATIONLIBRARY_HPP
#define CHEBYSHEVDIFFERENTIATIONLIBRARY_HPP

#include <cmath>
#include "Matrix.hpp"

class ChebyshevDifferentiationLibrary{

public:

    // Default Constructor.
    ChebyshevDifferentiationLibrary();

    /*
     * Function: FirstOrderDifferentiationMatrix
     * -----------------------------------------
     * Receives:
     *  A Vector object that represents a
     *  one-dimensional grid of nodes.
     * Returns:
     *  A n by n Matrix object with the entries of a
     *  First Order Chebyshev Differentiation matrix,
     *  where n is the size of the grid.
     *
     * (Computed using formulas)
     */
    Matrix FirstOrderDifferentiationMatrix(const Vector& grid);

    /*
     * Function: SecondOrderDifferentiationMatrix
     * -----------------------------------------
     * Receives:
     *  A Vector object that represents a
     *  one-dimensional grid of nodes.
     * Returns:
     *  A n by n Matrix object with the entries of a
     *  Second Order Chebyshev Differentiation matrix,
     *  where n is the size of the grid.
     *
     *(Computed using formulas)
     */
    Matrix SecondOrderDifferentiationMatrix(const Vector& grid);


};

#endif // CHEBYSHEVDIFFERENTIATIONLIBRARY_HPP
