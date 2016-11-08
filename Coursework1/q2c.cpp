#import <iostream>
#include <cmath>
#include "matrix_allocation.cpp"
#include "newton.cpp"

// A constant to hold the size of the system to be solved.
static const int DIM = 2;

/*
Function: f
Usage: double* f_x = f(a_vector);
-----------------------------------
Receives:
	.x_vec -> vector with 2 elements which you want 
	to evaluate the functions at.
Returns:
	.vector -> Result of the functions evaluated at x_vec.

Evaluates the two functions in the excercise sheet, at
the given 2x1 vector.
*/
double* f(double* x_vec);

/*
Function: Jf
Usage: double** Jf_x = Jf(a_vector);
-----------------------------------
Receives:
	.x_vec -> vector with 2 elements which you want 
	to evaluate in the Jacobian matrix.
Returns:
	.matrix -> A 2x2 matrix, which holds the result of 
	evaluating the given vector at the Jacobian matrix
	of the functions given in the excercise sheet.

Evaluates the given 2x1 vector in the Jacobian matrix
of the functions given in the excercise sheet.
*/
double** Jf(double* x_vec);

/*
Function: findMoreRoots
-------------------------
Used to spot the remaining three roots of the system.
*/
void findMoreRoots();

int main(){

	double init_guess[DIM] = {0.5, 0.5};
	double* a_root = newtonsMethod(f, Jf, init_guess, DIM);
	std::cout << "For seed:" << std::endl;
	printV(init_guess, DIM);
	std::cout << "I found this Root:" << std::endl;
	printV(a_root, DIM);
	std::cout << " " << std::endl;

	/* Evaluate the computed root at the functions 
	to see if it's zero.*/
	std::cout << "Is that a Root?" << std::endl;
	std::cout << "f(root) = " << std::endl;
	double* fx = f(a_root);
	printV(fx, DIM);
	std::cout << "l2 norm of f(root) = " ;
	std::cout << l2Norm(fx, DIM)<< std::endl;

	delete[] a_root;
	delete[] fx;

	/*
	Question asks us if we can spot any other solutions.
	The below function finds the remaining three roots of
	the system. (System has only got 4 roots).
	Uncomment the below function to print in the console
	the other 3 solutions found using other initial conditions.
	*/

	//findMoreRoots();
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

double** getSeeds(){
	/*
	Returns a 3x2 array holding the other three
	initial conditions neccessary to find the other
	three roots of the system.
	*/
	double** seeds = allocateMatrixMemory(3,2);

	double *seed1 = new double[DIM];
	seed1[0] = -.5; seed1[1] = .5;
	double *seed2 = new double[DIM];
	seed2[0] = .5; seed2[1] = -.5;
	double *seed3 = new double[DIM];
	seed3[0] = -.5; seed3[1] = -.5;

	seeds[0] = seed1; seeds[1] = seed2;
	seeds[2] = seed3;
	
	return seeds;
}

void findMoreRoots(){
	/*
	Runs newtons method with the other initial conditions
	to find the other three roots of the system.
	*/
	double** seeds = getSeeds();
	for (int i = 0; i<3; i++){
		double* seed = seeds[i];
		double* root = newtonsMethod(f, Jf, seed, DIM);
		std::cout << " " << std::endl;
		std::cout << "For seed:" << std::endl;
		printV(seed, DIM);
		std::cout << "I found this Root:" << std::endl;
		printV(root, DIM);
		std::cout << " " << std::endl;
	}
	std::cout << "Those are the only 4 roots of the system.\n";
	std:: cout << " " << std::endl;
	freeMatrixMemory(3, seeds);
}


