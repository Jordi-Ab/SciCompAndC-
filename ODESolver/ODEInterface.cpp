#include "ODEInterface.hpp"

// Implementation Section

ODEInterface::ODEInterface(MyFunctor& a_righthandside){
    _rhs = &a_righthandside;
    _true_sol = NULL;

}

void ODEInterface::ComputeF( const double t, const Vector& u, Vector& f ) const{
    (*_rhs)(t, u, f);
}

void ODEInterface::addTrueSolutionFunction(void (*function) (const double, Vector& )){
    _true_sol = function;
}

void ODEInterface::ComputeAnalyticSolution(const double t, Vector &u) const{
    if(_true_sol == NULL){
        throw std::runtime_error("No Analytical Solution Available.");
    }
    _true_sol(t, u);
}

Vector& ODEInterface::getDerivatives(){
    return _rhs->getDerivatives();
}
