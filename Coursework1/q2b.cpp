#import <iostream>
#include <cmath>
#include "matrix_allocation.cpp"
#include "newton.cpp"

// A constant to hold the size of the system to be solved.
static const int DIM = 3;

/*
Function: f
Usage: double* f_x = f(a_vector);
-----------------------------------
Receives:
	.x_vec -> vector with 3 elements which you want 
	to evaluate the functions at.
Returns:
	.vector -> Result of the functions evaluated at x_vec.

Evaluates the three functions in the excercise sheet, at
the given 3x1 vector.
*/
double* f(double* x_vec);

/*
Function: Jf
Usage: double** Jf_x = Jf(a_vector);
-----------------------------------
Receives:
	.x_vec -> vector with 3 elements which you want 
	to evaluate in the Jacobian matrix.
Returns:
	.matrix -> A 3x3 matrix, which holds the result of 
	evaluating the given vector at the Jacobian matrix
	of the functions given in the excercise sheet.

Evaluates the given 3x1 vector in the Jacobian matrix
of the functions given in the excercise sheet.
*/
double** Jf(double* x_vec);

int main(){
	double init_guess[DIM] = {0.5, 0.5, 0.5};
	double* a_root = newtonsMethod(f, Jf, init_guess, DIM);
	std::cout << "Root:" << std::endl;
	printV(a_root, DIM);
	std::cout << " " << std::endl;

	std::cout << "Is that a Root?" << std::endl;
	std::cout << "f(root) = " << std::endl;
	/* Evaluate the computed root at the functions 
	to see if it's zero.*/
	double* fx = f(a_root);
	printV(fx, DIM);
	std::cout << "l2 norm of f(root) = " ;
	std::cout << l2Norm(fx, DIM)<< std::endl;

	delete[] a_root;
	delete[] fx;	
}

double* f(double* x_vec){
	double x1 = x_vec[0]; 
	double x2 = x_vec[1]; 
	double x3 = x_vec[2];

	double* result = new double[DIM];
	result[0] = pow(x1, 2.0) + pow(x2, 2.0) + pow(x3, 2.0) - 1;
	result[1] = 2*pow(x1, 2.0) + pow(x2, 2.0) - 4*x3;
	result[2] = 3*pow(x1, 2.0) - 4*x2 + pow(x3, 2.0);

	return result;
}

double** Jf(double* x_vec){
	double x1 = x_vec[0]; 
	double x2 = x_vec[1]; 
	double x3 = x_vec[2];

	double** J = allocateMatrixMemory(DIM,DIM);
	J[0][0]=2*x1; J[0][1]=2*x2; J[0][2]= 2*x3;
	J[1][0]=4*x1; J[1][1]=2*x2; J[1][2]= -4;
	J[2][0]=6*x1; J[2][1]=-4; J[2][2]= 2*x3;

	return J;
}

