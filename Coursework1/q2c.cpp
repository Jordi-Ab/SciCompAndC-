#import <iostream>
#include <cmath>
#include "matrix_allocation.cpp"
#include "newton.cpp"

static const int DIM = 2;

double* f(double* x_vec);
double** Jf(double* x_vec);

int main(){

	double init_guess[DIM] = {0.5, 0.5};
	double* a_root = newtonsMethod(f, Jf, init_guess, DIM);
	std::cout << "Root:" << std::endl;
	printV(a_root, DIM);
	std::cout << " " << std::endl;

	std::cout << "Is that a Root?" << std::endl;
	std::cout << "f(root) = " << std::endl;
	double* fx = f(a_root);
	printV(fx, DIM);
	std::cout << "l2 norm of f(root) = " << l2Norm(fx, DIM)<< std::endl;
}

double* f(double* x_vec){
	double x1 = x_vec[0]; 
	double x2 = x_vec[1]; 

	double* result = new double[DIM];
	result[0] = pow(x1, 2.0) + pow(x2, 2.0) - 1;
	result[1] = 5*pow(x1, 2.0) + 21*pow(x2, 2.0) - 9;

	return result;
}

double** Jf(double* x_vec){
	double x1 = x_vec[0]; 
	double x2 = x_vec[1]; 

	double** J = allocateMatrixMemory(DIM,DIM);
	J[0][0]=2*x1; J[0][1]=2*x2;
	J[1][0]=10*x1; J[1][1]=42*x2;

	return J;
}

