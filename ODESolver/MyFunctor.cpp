#include "MyFunctor.hpp"

MyFunctor::MyFunctor(const double a){
    _my_constant = a;

    // States are zero for this example.
    _states_vector = new Vector(1);
    (*_states_vector)[0] = 0;
}

void MyFunctor::operator() (const double t, const Vector& u, Vector& result){
    result[0] = 1/(_my_constant + pow(t, 2.0));
}

Vector& MyFunctor::getDerivatives(){
    return *_states_vector;
}


