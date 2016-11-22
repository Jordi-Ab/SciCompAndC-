#include <cmath>
#include "matrix_allocation.hpp"

double* GCLmesh(int n){
	double* mesh = new double[n];
	for (int j=0; j<n; j++){
		double xj = cos(j*M_PI/n);
		mesh[j] = xj;
	}
	return mesh;
}

double** chebyDiffMatrix(int n, double* x){
	double** d_mat = allocateMatrixMemory(n,n);
	for (int i=0; i<n; i++){
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
			d_mat[i][j] = entry;
		}
	} 
	return d_mat;
}
