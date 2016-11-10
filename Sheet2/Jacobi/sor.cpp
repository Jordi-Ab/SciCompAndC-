#include <iostream>

double* substractV(double *v1, double *v2, int size);
double* addV(double *v1, double *v2, int size);
double* vectorTimesConstant(double* vector, double constant, int size);
double l2Norm(double* a_vector, int size);

double* gsStep(double** A, double* b, double* last_x, int size);

double* sorSolve(double** A, double* b, double* initial_x, double omega, int size){
    /*
     * Solves the Linear System Ax = b using the Jacobi
     * stationary iterative procedure.
     */
    int iterations = 0;
    int tolerance = 100000;
    double* last_x = initial_x;
    double* new_x = NULL;

    while (true){

        new_x = gsStep(A, b, last_x, size);
        iterations += 1;

        double* difference = substractV(new_x, last_x, size);
        if (l2Norm(difference, size)<=1e-10){
            std::cout << "SOR Method converged in ";
            std::cout << iterations << " iterations." << std::endl;
            break;
        }else if (iterations >= tolerance){
            std::cout << "SOR failed to converge after ";
            std::cout << iterations << " iterations." << std::endl;
            return NULL;
        }

        double* directed_v = vectorTimesConstant(difference, omega, size);
        last_x = addV(last_x, directed_v, size);
        last_x = new_x;

    }

    return new_x;

}
