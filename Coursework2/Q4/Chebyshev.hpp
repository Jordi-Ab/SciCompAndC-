
/*
Function: GCLmesh
-------------------------------------
Receives an empty pointer "mesh" with
given size. Fills it in with the 
Gauss-Chebyshev-Lobatto mesh points, 
defined as:

xj = cos(jπ/n), j = 0,1,...,n,
*/
void GCLmesh(int n, double* mesh){

	for (int j=0; j<=n; j++){
		double xj = cos(j*M_PI/n);
		mesh[j] = xj;
	}
}

/*
Function: ChebyshevDifferentiationMatrix
-------------------------------------
Receives an empty pointer to a matrix "D"
given size. Fills it in with the entires of a
first order Chebyshev Differentiation Matrix.
*/
void ChebyshevDifferentiationMatrix(int n, double* x, double **D)