#include <iostream>
#include "ForwardEulerSolver.hpp"
#include <cmath>

double f(double t, double y);
double true_sol(double t);

int main(){

    double (*func) (double, double);

    func = &f;
    double y0 = 0;
    double T = 10;
    double h=.01;

    ForwardEulerSolver method = ForwardEulerSolver(func, y0, T, h);
    method.solve();

    return 0;
}

double f(double t, double y){
    const double a = 1;
    return 1/(a + pow(t, 2.0));
}

double true_sol(double t){
    const double a = 1;
    return (1/sqrt(a)) * atan(t/sqrt(a));
}
