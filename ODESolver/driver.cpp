#include <iostream>
#include "ForwardEulerSolver.hpp"
#include "ODEInterface.hpp"
#include <cmath>
#include "Vector.hpp"
#include "MyFunctor.hpp"

void f(const double t, const Vector& u, Vector& dxdt);
void true_sol(const double t, Vector& result);


int main(){

    // initialize all the necessary info of the problem:
    const int a = 1;
    void (*solution) (const double t, Vector&) = &true_sol;
    Vector y0(1); y0[0] = 0; // Initial Conditions.
    double t0 = 0; // initial time.
    double T = 10; // final time
    double h=.01; // step size
    std::string output_file_name = "fwd_euler_output.dat";

    //The rhs of x' = f(t, x) defined as a class MyFunctor.
    MyFunctor rhs(a);

    // Instantiate an ODE Interface with the right hand side function.
    ODEInterface odeint(rhs);

    /* As we have an analytical solution to this problem, we can give it to
    the Interface in order to compare results.*/
    odeint.addTrueSolutionFunction(solution);

    /* Instantiate the method to be used, in this case ForwardEuler,
    and provide all the necessary information for the steps.*/
    ForwardEulerSolver method(odeint,y0,t0,T,h,output_file_name,1,1);

    //Solve the IVP by a simple call to solve()
    method.solve();


    return 0;
}

void f(const double t, const Vector& u, Vector& dxdt){
    const double a = 1;
    dxdt[0] = 1/(a + pow(t, 2.0));
}

void true_sol(const double t, Vector& result){
    const double a = 1;
    result[0] = (1/sqrt(a)) * atan(t/sqrt(a));
}
