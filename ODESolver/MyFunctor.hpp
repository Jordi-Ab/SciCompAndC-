#ifndef MYFUNCTOR_HPP
#define MYFUNCTOR_HPP

#include "Vector.hpp"
#include <cmath>
class MyFunctor{

public:

    MyFunctor(const double a);

    /*
     * Operator: ()
     * ---------------
     * To evaluate the "function"
     * at the given values.
    */
    void operator() (const double t, const Vector& u, Vector& dxdt);

    /*
     * Function: getDerivatives
     * ------------------------
     * Returns the instance vector _dudt.
    */
    Vector& getDerivatives();

private:

    double _my_constant;

    // Vector of derivatives.
    Vector* _dudt;

};

#endif // MYFUNCTOR_HPP
