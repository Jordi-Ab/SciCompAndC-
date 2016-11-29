#include <iostream>
#include <string>
#include "Chebyshev.cpp"
#include "InputOutputUtilities.cpp"
#include "VecsAndMats.cpp"/*
Compile the .cpp files just once in the Driver*/

const int MAX_N = 20;

double* f(double* xs, int n);
double f(double x);

double* df(double* xs, int n);
double df(double x);

// Saves vectors to files.
void _saveVectors(int n, double* mesh, 
				double* approx_sol, 
				double*true_deriv);

int* _ns();

int main(){
	int* ns = _ns(); // ns = [2,4,6,8,...,40]
	double* errors = new double[MAX_N];
	for (int i=0; i<MAX_N; i++){
		int n = ns[i]+1;
		
		double* mesh = new double[n];
		double** D = allocateMatrixMemory(n,n);

		ChebyshevDifferentiationMatrix(n-1, mesh, D);
		
		double* us = f(mesh, n);

		double* approx_sol = matrixTimesVector(D, us, n,n,n);
		
		double* true_deriv = df(mesh, n);
	
		double* residual = substractV(true_deriv, approx_sol, n);

		double error = infinityNorm(residual, n);

		errors[i] = error;

		std::cout << "For n = " << n << ", ";
		std::cout << "error = " << error << std::endl;

		if(n-1 == 2*MAX_N){/*
		Last iteration of the for
		Save vectors before they are deleted:*/
			_saveVectors(n, mesh, approx_sol, true_deriv);
		}

		delete[] mesh;
		freeMatrixMemory(n, D);
		delete[] us;
		delete[] approx_sol;
		delete[] true_deriv;
		delete[] residual;
}
	SaveVectorToFile(MAX_N, errors, "error.dat");
	delete[] ns;
}

void _saveVectors(int n, double* mesh, 
				double* approx_sol, 
				double*true_deriv){

	bool use_complete_path = false;
	std::string cwd = "";
	if(use_complete_path){
		cwd = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework2/Q4/";
	}/*
	On my computer, c++ doesn't save the files
	in the current working directory, so I have
	to provide the full path of the working dir.*/

	SaveVectorToFile(n, mesh, "grid.dat");
	SaveVectorToFile(n, approx_sol, "du_numerical.dat");
	SaveVectorToFile(n, true_deriv, "du_analytical.dat");
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