

/*
Function: backSubstitution
Usage: double* vec_x = backSubstitution(a_matrix, 4, 5)
-----------------------------------
Receives: 
	."aug_matrix" -> An augmented upper triangular matrix,
	."n_rows" -> The number of rows in the augmented matrix.
	."n_cols" -> The number of columns in the augmented matrix.
performs backward substitution on that matrix,
to solve the linear system Ax = b.

Returns the resulting vector x.

Important: 
Assumes the given matrix is in upper triangular form,
and is an augmented matrix.

i.e.
|  1  2 -3 -6  2 |
|  0 -8  2  1 -3 |
|  0  0  3 -5  1 |
|  0  0  0  2 -1 |

Here b is the last column of the matrix, so aug_matrix = |Ab| 
with A = 4x4 matrix, and b = 4x1 vector.
Hence, augmented matrix is of size 4x5.
*/
double* backSubstitution(double** aug_matrix,int n_rows,int n_cols){
	
    double* result;
	result = new double[n_rows];
	
    for(int i=n_rows-1; i>=0; i--){
		
        double rhs = aug_matrix[i][n_cols-1]; // rhs stands for right hand side.
		
        for(int j=n_rows-1; j>i; j--){
			rhs -= result[j]*aug_matrix[i][j];
		}
		
        result[i] = rhs/aug_matrix[i][i];
	}
	
    return result;
}
