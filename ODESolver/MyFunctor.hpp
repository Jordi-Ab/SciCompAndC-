/*******************************************************
MyFunctor object that wrapps functions of the form:

f(u(t), t) where:
    u(t) is a vector of states
    t is a time variable.

that are used as right hand side functions for ODE's.

For the ODEInterface to accept this functor as
right hand side function:

f must be a void function with three parameters:
    . const double t    -> A constant for the time variable
    . const Vector& u   -> A constant vector of states.
    . Vector& result    -> A vector that will be overriden
                            and will store the result of the
                            evaluation.

# Eventhough your function doesn't involve either u or t,
# they must be provided, as the ODEInterface make use of them.
*******************************************************/

#ifndef MYFUNCTOR_HPP
#define MYFUNCTOR_HPP

#include "Vector.hpp"
#include <cmath>
class MyFunctor{

public:

    /*
     * Constructor: MyFunctor
     * ---------------
     * Initializes the Object.
     * The constant "a" involved in the function
     * must be provided.
    */
    MyFunctor(const double a);

    /*
     * Operator: ()
     * ---------------
     * To evaluate the "function"
     * at the given values.
    */
    void operator() (const double t, const Vector& u, Vector& result);

    /*
     * Function: getDerivatives
     * ------------------------
     * Returns the instance vector of states.
    */
    Vector& getDerivatives();

private:

    // In this case the function involves a constant
    double _my_constant;

    // Vector of states.
    Vector* _states_vector;

};

#endif // MYFUNCTOR_HPP
