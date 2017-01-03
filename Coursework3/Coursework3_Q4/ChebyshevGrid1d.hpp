#ifndef CHEBYSHEVGRID1D_HPP
#define CHEBYSHEVGRID1D_HPP

#include <cmath>
#include "Vector.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>
#include "ChebyshevDifferentiationLibrary.hpp"

// I want ChebyshevGrid1D to "be a" Vector. i.e.
// to inherit all it's public members.
class ChebyshevGrid1D:public Vector{

public:

    // Creates an object containing n + 1
    //Gauss–Lobatto nodes in the interval [-1,1].
    ChebyshevGrid1D(const int n);

    //~ChebyshevGrid1D();

    // Overriden operator <<
    // To display the coordinates of the grid on screen.
    friend std::ostream& operator<<(std::ostream& output,
                                    ChebyshevGrid1D& grid);

private:

    // Continer for the Nodes coordinates.
    Vector* _nodes;

};

#endif // CHEBYSHEVGRID1D_HPP
