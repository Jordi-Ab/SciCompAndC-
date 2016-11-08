#include <iostream>
/*
Function: dot
Usage: double dot_prod = dot(one_vec, another_vec, their_size);
-------------------
Computes the Dot Product between two vectors.
Receives two vectors. "v1" and "v2", and the size of this vectors.
(To perform a dot product both vectors must have the same size)
Returns a double that is the dot product between the two vectors. 
v1[0]*v2[0] + ... + v1[n]*v2[n].
 
#Assumes both vectors have the same size.
 
*/ 
double dot(double *v1, double *v2, int size){
	double dot_prod = 0;
	for (int i=0; i<size; i++){
		dot_prod += v1[i] * v2[i];
	}
	return dot_prod;
}

/*
Function: matrixTimesVector
Usage: double* resulting_vec = matrixTimesVector(a_matrix, a_vector, 5, 4, 4);
-------------------
Multiplies a Matrix times a Vector.
Receives:
	."matrix" -> A matrix with mat_rows number of rows, and mat_cols columns
	."vector" -> A vector with vec_rows and 1 column.
	."mat_rows" -> The number of rows on the matrix.
	."mat_cols" -> The number of cols on the matrix.
	."vec_rows" -> The number of rows on the vector.
Returns: a vector that holds the result of the multiplication. 
#Note:
	(The number of columns in the matrix, must equal 
	the number of rows in the vector.)
*/ 
double* matrixTimesVector(double **matrix, double *vector, int mat_rows, int mat_cols, int vec_rows){
	double* result;
	if (mat_cols != vec_rows){
		std::cout << "Can't multiply "<< mat_rows << "x" << mat_cols;
		std::cout << "matrix, with a "<< vec_rows << "x1 vector."<<std::endl;
		result = NULL;
	}else{
		result = new double[mat_rows];
		for (int i=0; i<mat_rows; i++){
			result[i] = dot(matrix[i],vector, mat_cols);
		}
	}
	return result;
}
