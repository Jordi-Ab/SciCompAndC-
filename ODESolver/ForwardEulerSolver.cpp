#include "ForwardEulerSolver.hpp"

ForwardEulerSolver::ForwardEulerSolver(ODEInterface& an_ODESystem,
                                       const Vector& initial_value,
                                       const double initial_time,
                                       const double final_time,
                                       const double step_size,
                                       const std::string output_file_name,
                                       const int save_gap,
                                       const int print_gap){

    // Set things for AbstractODE object.
    setInitialValue(initial_value);
    setStepSize(step_size);
    setTimeInterval(initial_time, final_time);
    _ODEObject = &an_ODESystem;

    // Set things for this object.
    _output_file_name = output_file_name;
    _save_gap = save_gap;
    _print_gap = print_gap;

}


// A solver that saves the soultion on vectors and then writes those
// vectors to an output file.
/*
void ForwardEulerSolver::solve(){

    int n = getFinalTime()/getStepSize(); // Number of steps
    std::cout << "n: " << n << std::endl;
    double h = getStepSize();
    std::cout << "h: " << h << std::endl;

    double* ys = new double[n];
    double* ts = new double[n];

    ys[0] = getInitialValue();
    ts[0] = 0;

    for(int i=0; i<n-1; i++){
        double next_t = ts[i] + h;
        std::cout << "  next_t: " << next_t << std::endl;
        ts[i+1] = next_t;
        double next_y = ys[i] + h*rightHandSide(ts[i], ys[i]);
        std::cout << "  next_y: " << next_y << std::endl;
        ys[i+1] = next_y;
    }

    saveSolution("output.dat", ts, ys, n);
    delete[] ts;
    delete[] ys;

}*/

// A solver that writes the solution on an Output file at
// each time step (no need of arrays to store solution).
void ForwardEulerSolver::solve(){

    int n = getFinalTime()/getStepSize(); // Number of steps
    std::cout << "n: " << n << std::endl;
    double h = getStepSize();
    std::cout << "h: " << h << std::endl;

    Vector derivs = _ODEObject->getDerivatives(); // Vector of u's

    openOutputFile(_output_file_name);

    Vector current_y = getInitialValue();
    Vector next_y(current_y);
    double current_t = getInitialTime();

    while(current_t < getFinalTime()){
        writeData(current_t, current_y[0]); // Which data you want, the one at 0?
        double next_t = current_t + h;
        std::cout << "  next_t: " << next_t << std::endl;
        _ODEObject->ComputeF(current_t, derivs, next_y); // Evaluate f
        next_y = current_y + next_y*h;
        std::cout << "  next_y: " << next_y << std::endl;

        current_t = next_t;
        current_y = next_y;
    }

    closeOutputFile();

}




