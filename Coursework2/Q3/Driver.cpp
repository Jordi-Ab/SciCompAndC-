#include <iostream>
#include "Chebyshev.cpp"
#include "InputOutputUtilities.cpp"
#include "matrix_allocation.cpp"
#include "VecsAndMats.cpp"

const int MAX_N = 20;

double* f(double* xs, int n);
double f(double x);

double* df(double* xs, int n);
double df(double x);

int* _ns();
double infinityNorm(double* a_vector, int size);

int main(){
	int* ns = _ns();
	double* errors = new double[MAX_N];
	for (int i=0; i<MAX_N; i++){
		int n = ns[i]+1;
		//int n=10;

		double* mesh = new double[n];
		double** D = allocateMatrixMemory(n,n);

		ChebyshevDifferentiationMatrix(n-1, mesh, D);
		//PrintVector(n+1, mesh, "mesh");
		//PrintMatrix(n+1,n+1, D, "Diff");

		
		double* us = f(mesh, n);
		//PrintVector(n+1, us, "us");

		// D is symmetric, then you can just make half of the step for multiplication.
		double* approx_sol = matrixTimesVector(D, us, n,n,n);
		//PrintVector(n+1, approx_sol, "approx_sol");
		double* true_deriv = df(mesh, n);
		//PrintVector(n+1, true_deriv, "true_sol");
		double* residual = substractV(true_deriv, approx_sol, n);
		//PrintVector(n+1, residual, "residual");
		double error = infinityNorm(residual, n);

		errors[i] = error;

		std::cout << "For n = " << n << ", ";
		std::cout << "error = " << error << std::endl;

		if(n-1 == 2*MAX_N){
		// Save vectors:
			std::cout << "Saving vectors to files" << std::endl;
			SaveVectorToFile(n, mesh, "grid.dat");
			SaveVectorToFile(n, approx_sol, "du_numerical.dat");
			SaveVectorToFile(n, true_deriv, "du_analytical.dat");
		}

		delete[] mesh;
		freeMatrixMemory(n, D);
		delete[] us;
		delete[] approx_sol;
}
	PrintVector(MAX_N, errors, "errors");
	SaveVectorToFile(MAX_N, errors, "error.dat");
	delete[] ns;
}

double infinityNorm(double* a_vector, int size){
	double max_entry = std::abs(a_vector[0]);
	for (int i=1; i<size; i++){
		double next_entry = std::abs(a_vector[i]);
		if(next_entry > max_entry){
			max_entry = next_entry;
		}
	}
	return max_entry;
}

double* f(double* xs, int n){
	double* f_at = new double[n];
	for (int i=0; i<n; i++){
		double x = f(xs[i]);
		f_at[i] = x;
	}
	return f_at;
}
double f(double x){
	return exp(x)*sin(5*x);
}


double* df(double* xs, int n){
	double* df_at = new double[n];
	for (int i=0; i<n; i++){
		double x = df(xs[i]);
		df_at[i] = x;
	}
	return df_at;
}
double df(double x){
	return exp(x)*( 5*cos(5*x) + sin(5*x) );
}

int* _ns(){
	int* array = new int[20];
	for (int i=1; i<=20; i++){
		array[i-1] = 2*i; 
	}
	return array;
}