
#import <iostream>
#import <cmath>
#include "solve_ax_eq_b.cpp"

double l2Norm(double* a_vector, int size){
	double norm = 0.0;
    for (int i=0; i<size; i++){
        norm += pow(a_vector[i],2.0);
    }
    return sqrt(norm);
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

void printMat(double **matrix, int n_rows, int n_cols){
	for (int row=0; row < n_rows; row++){
		std::cout << "|";
		for (int col=0; col<n_cols; col++){
			if (matrix[row][col]>=0 && matrix[row][col]<10) std::cout << " ";
			std::cout << matrix[row][col] << " ";
		}
		std::cout << "|" << std::endl;
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


double* newtonsMethod(double* (f)(double*), 
						double** (Jf)(double*), 
						double* x_vec, int dim,
						double error_tol=1e-6,
						int max_iter=100){

	double iterations = 0;
	double* result = _copy(x_vec, dim);
	double* step;

	while (true){

		step = solveAxEqB((Jf)(result), (f)(result), dim);
		if(l2Norm(step, dim)<error_tol) break;
		
		result=_substractV(result, step, dim);

		iterations++;

		if(iterations >= max_iter){
			std::cout << "Newtons Method exceeded number of iterations." << std::endl;
			return NULL;
		}
	}
	return result;
}
