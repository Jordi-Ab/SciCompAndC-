#include <iostream>

double* substractV(double *v1, double *v2, int size);
double l2Norm(double* a_vector, int size);

double* jacobiStep(double** A, double* b, double* last_x, int size){
    double* x_new = new double[size];
    for (int r=0; r<size; r++){
        x_new[r] = b[r];
        for (int c=0; c<size; c++){
            if (r != c) x_new[r] -= A[r][c]*last_x[c];
        }
        x_new[r] = x_new[r] / A[r][r];
     }
    return x_new;
}

double* jacobiSolve(double** A, double* b, double* initial_x, int size){
    /*
     * Solves the Linear System Ax = b using the Jacobi
     * stationary iterative procedure.
     */
    int iterations = 0;
    int tolerance = 100000;
    double* last_x = initial_x;
    double* new_x = NULL;
    while (true){
        new_x = jacobiStep(A, b, last_x, size);
        iterations += 1;
        double* difference = substractV(new_x, last_x, size);
        if (l2Norm(difference, size)<=1e-10){
            std::cout << "Jacobi Method converged in ";
            std::cout << iterations << " iterations." << std::endl;
            break;
        }else if (iterations >= tolerance){
            std::cout << "Jacobi failed to converge after ";
            std::cout << iterations << " iterations." << std::endl;
            return NULL;
        }
        last_x = new_x;
    }
    return new_x;
}



