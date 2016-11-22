#include "Chebyshev.cpp"
#include "InputOutputUtilities.cpp"
#include "matrix_allocation.cpp"
#include "VecsAndMats.cpp"

double* f(double* xs, int n);
double f(double x);

double* df(double* xs, int n);
double df(double x);

int main(){
	int n = 10;

	double* mesh = GCLmesh(n);
	double** D = chebyDiffMatrix(n, mesh);

	double* us = f(mesh, n);
	double* approx_sol = matrixTimesVector(D, us, n,n,n);
	
}

double infiniteNorm(double* a_vector, int size){
	int max_entry = a_vector[0];
	for (int i=1; i<size; i++){
		if(a_vector[i] > max_entry){
			max_entry = a_vector[i];
		}
	}

}

double* f(double* xs, int n){
	double* f_at;
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
	double* df_at;
	for (int i=0; i<n; i++){
		double x = df(xs[i]);
		df_at[i] = x;
	}
	return df_at;
}
double df(double x){
	return exp(x)*( 5*cos(5*x) + sin(5*x) );
}