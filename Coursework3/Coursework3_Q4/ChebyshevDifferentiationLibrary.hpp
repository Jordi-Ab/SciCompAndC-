#ifndef CHEBYSHEVDIFFERENTIATIONLIBRARY_HPP
#define CHEBYSHEVDIFFERENTIATIONLIBRARY_HPP

#include <cmath>
#include "Matrix.hpp"
#include "ChebyshevGrid1d.hpp"

class ChebyshevDifferentiationLibrary{

public:

    // Default constructor.
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
     */
    Matrix SecondOrderDifferentiationMatrix(const Vector& grid);

    Matrix LaplacianDifferentiationMatrix(const Vector& x_grid,
                                        const Vector& y_grid);

    // Returns a n by n Identity
    // Matrix Object. i.e.
    // 1's on the diagonal,
    // and 0's everywhere else.
    Matrix eye(int n);


};



#endif // CHEBYSHEVDIFFERENTIATIONLIBRARY_HPP
