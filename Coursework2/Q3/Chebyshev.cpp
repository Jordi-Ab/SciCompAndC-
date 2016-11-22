#include <cmath>
#include "matrix_allocation.hpp"

void GCLmesh(int n, double* mesh){

	for (int j=0; j<n; j++){
		double xj = cos(j*M_PI/n);
		mesh[j] = xj;
	}
}

void ChebyshevDifferentiationMatrix(int n, double* x, double **D){
	GCLmesh(n, x);
	for (int i=0; i<n; i++){
		//double xi = cos(i*M_PI/n);
		//x[i] = xi;
		for (int j=0; j<n; j++){
			double entry;
			if(i==0 && j==0){
				entry = (2*pow(n,2.0) + 1)/6;
			}else if(i==n-1 && j==n-1){
				entry = - (2*pow(n,2.0) + 1)/6;
			}else if (i==j){
				entry = -x[j]/(2*( 1-pow(x[j],2) ) );
			}else{
				int ci = (i==0 || i==n) ? (2):(1);
				int cj = (j==0 || j==n) ? (2):(1);
				entry = (ci/cj) * ( pow(-1, i+j) / (x[i] - x[j]) );
			}
			D[i][j] = entry;
		}
	} 
}
