#ifndef CHEBYSHEVGRID1D_HPP
#define CHEBYSHEVGRID1D_HPP

#include <cmath>
#include "Vector.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>

/* ChebyshevGrid1D "is a" Vector. i.e.
 * inherits all it's public members.*/
class ChebyshevGrid1D:public Vector{

public:

    /* Constructor: ChebyshevGrid1D;
     * -----------------------------------------
     * Creates an object containing n + 1
     * Gauss–Lobatto nodes in the interval [-1,1].
     */
    ChebyshevGrid1D(const int n);

    /* Operator: <<
     * ----------------------------------------
     * Displays the coordinates of the grid on screen,
     * vertically.
     * i.e. [-1, grid[1], ..., grid[n], 1]
     */
    friend std::ostream& operator<<(std::ostream& output,
                                    ChebyshevGrid1D& grid);

private:

    /* Pointer for the Nodes coordinates.
     * This object gets initialized as a Vector, though
     * we can't overwrite its "mData" instance. But,
     * we can make a pointer that points to "this" vector,
     * that way we can overwrite the data of "this" vector
     * using "_nodes" pointer. (see the constructor code).
     */
    Vector* _nodes;

};

#endif // CHEBYSHEVGRID1D_HPP
