#include <iostream>
#include "Chebyshev.cpp"
#include "InputOutputUtilities.cpp"
#include "matrix_allocation.cpp"
#include "VecsAndMats.cpp"

double* f(double* xs, int n);
double f(double x);

double* df(double* xs, int n);
double df(double x);

int* _ns();
double infinityNorm(double* a_vector, int size);

int main(){
	int* ns = _ns();
	for (int i=0; i<20; i++){
		int n = ns[i];

		//int n=10;

		double* mesh = new double[n+1];
		double** D = allocateMatrixMemory(n+1,n+1);

		ChebyshevDifferentiationMatrix(n, mesh, D);
		//PrintVector(n+1, mesh, "mesh");
		//PrintMatrix(n+1,n+1, D, "Diff");

		
		double* us = f(mesh, n+1);
		//PrintVector(n+1, us, "us");

		// D is symmetric, then you can just make half of the step for multiplication.
		double* approx_sol = matrixTimesVector(D, us, n+1,n+1,n+1);
		//PrintVector(n+1, approx_sol, "approx_sol");
		double* true_deriv = df(mesh, n+1);
		//PrintVector(n+1, true_deriv, "true_sol");
		double* residual = substractV(true_deriv, approx_sol, n+1);
		//PrintVector(n+1, residual, "residual");
		double error = infinityNorm(residual, n+1);

		std::cout << "For n = " << n << ", ";
		std::cout << "error = " << error << std::endl;

		delete[] mesh;
		freeMatrixMemory(n+1, D);
		delete[] us;
		delete[] approx_sol;
	}
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