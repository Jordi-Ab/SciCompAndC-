#import <iostream>
#include <cmath>
#include "matrix_allocation.cpp"
#include "newton.cpp"

static const int DIM = 3;

void printV(double *vector, int size);
double* f(double* x_vec);
double** Jf(double* x_vec);

int main(){
	double init_guess[DIM] = {0.5, 0.5, 0.5};
	double* a_root = newton(f, Jf, init_guess, DIM);

	std::cout << "Root:"<<std::endl;
	printV(a_root, DIM);
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

void printV(double *vector, int size){
	if(vector == NULL){
		std::cout << "NULL vector" << std::endl;
	}else{
		for (int i=0; i<size; i++){
			if (vector[i]>=0 && vector[i]<10) std::cout << "| ";
			else std::cout << "|";
			if (isAlmostZero(vector[i])) std::cout << 0 << "|" << std::endl;
			else std::cout << vector[i] << "|" << std::endl;
		}
	}
}
