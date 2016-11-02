#include <stdexcept>
#import <iostream>
#include "solve_ax_eq_b.cpp"

void _printV(double *vector, int size){
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

double* _substractV(double *v1, double *v2, int size){
	double* result;
	result = new double[size];
	for (int i=0; i<size; i++){
		result[i] = v1[i] - v2[i];
	}
	return result;
}

double* _copy(double* a_vector, int size){
	double* new_vec;
	new_vec = new double[size];
	for(int i=0; i<size; i++){
		new_vec[i] = a_vector[i];
	}
	return new_vec;
}

void _newtonsMethod(double* (f)(double*), 
						double** (Jf)(double*), 
						double* x_vec, int dim,
						double error_tol,
						int max_iter){
	double iterations = 0;
	while (true){
		std::cout<< "Iteration: " << iterations << std::endl;
		double* step = solveAxEqB((Jf)(x_vec), (f)(x_vec), dim);
		x_vec=_substractV(x_vec, step, dim);
		std::cout<< "x_vec: " << iterations << std::endl;
		_printV(x_vec, dim);
		iterations += 1;
		if(iterations >= max_iter){
			std::runtime_error(
			"Newtons Method exceeded number of iterations.");
		}
		// function isVectorAlmostZero is in "solve_ax_eq_b.cpp"
		std::cout<< "step: " << std::endl;
		_printV(step, dim);
		std::cout<< "isAlmostZero?: "<< isVectorAlmostZero(step, error_tol) << std::endl;
		if(isVectorAlmostZero(step, error_tol)) break; // bug in is almost zero
	}
}

double* newton(double* (f)(double*), 
			double** (Jf)(double*), 
			double* x_vec, int dim,
			double error_tol=1e-6,
			int max_iter = 100){

	double* result = _copy(x_vec, dim);

	try{ 
		_newtonsMethod(f,Jf,result,dim,error_tol, max_iter); 
		std::cout << "After newton converged:" << std::endl;
		_printV(result, dim);
	}catch (const std::runtime_error& problem){	// Convergence failure.
		std::cout << problem.what() << std::endl; // Prints out the error message.
		return NULL; // Return a pointer to NULL.
	}
	return result; // Solution found.
}