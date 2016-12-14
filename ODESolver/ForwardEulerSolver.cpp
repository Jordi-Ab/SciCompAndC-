#include "ForwardEulerSolver.hpp"

ForwardEulerSolver::ForwardEulerSolver(double (*f)(double t, double y),
                                       double initial_value, double final_time,
                                       double step_size){
    setInitialValue(initial_value);
    setStepSize(step_size);
    setTimeInterval(0, final_time);
    _rhs = f;

}

double ForwardEulerSolver::rightHandSide(double t, double y){
    return _rhs(t,y);
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

    openOutputFile("fwd_euler_output.dat");

    double current_y = getInitialValue();
    double current_t = 0;

    while(current_t < getFinalTime()){
        writeData(current_t, current_y);
        double next_t = current_t + h;
        std::cout << "  next_t: " << next_t << std::endl;
        double next_y = current_y + h*rightHandSide(current_t, current_y);
        std::cout << "  next_y: " << next_y << std::endl;

        current_t = next_t;
        current_y = next_y;
    }

    closeOutputFile();

}




