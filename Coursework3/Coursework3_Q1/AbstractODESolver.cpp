#include "AbstractODESolver.hpp"
#include <stdexcept>

AbstractODESolver::AbstractODESolver()
{

}

void AbstractODESolver::setStepSize(double h){
    if(h < 0 || h >=1){
        throw std::runtime_error("Invalid value for step size h. Must be between 0 and 1.");
    }
    _h = h;
}

void AbstractODESolver::setTimeInterval(double initial_t, double final_t){
    if(final_t <= initial_t){
        throw std::runtime_error("Invalid time interval.");
    }
    _final_time = final_t;
    _initial_time = initial_t;
}

void AbstractODESolver::setInitialValue(double y0){
    _initial_value = y0;
}

void AbstractODESolver::setRHS(double (*RHS)(double, double)){
    // Has to do with the ODE Interface.
}

double AbstractODESolver::getStepSize(){
    return _h;
}

double AbstractODESolver::getInitialTime(){
    return _initial_time;
}

double AbstractODESolver::getFinalTime(){
    return _final_time;
}

double AbstractODESolver::getInitialValue(){
    return _initial_value;
}

// PRIVATE METHODS.
double* linspace(double low, double high, int n){
    double* range = new double[n];
    double h = (high - low)/(n-1);
    range[0] = low;
    for (int i=1; i<n-1; i++){
        range[i] = range[i-1] + h;
    }
    range[n-1] = high;
    return range;
}


