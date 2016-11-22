#include <iostream>
#include <cmath>
#include "VecsAndMats.cpp"

/*
Function: allocateMatrixMemory
Usage: double** a_matrix = allocateMatrixMemory(2, 3)
---------------------------------------------
Saves space in the computer's memory to hold a
matrix of n_rows by n_cols size.
*/
double** createMatrix(int n_rows, int n_cols);

/*
Function: freeMatrixMemory
Usage: freeMatrixMemory(2, a_matrix)
--------------------------------------------------
Receives the number of rows of the matrix, and the
matrix itself for which you want to free the memory space. 
Deallocates the memory used by the given matrix.
*/
void deleteMatrix(int n_rows, double** matrix);

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
double dot(double *v1, double *v2, int size);

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
double* matrixTimesVector(double **matrix, double *vector, int mat_rows, int mat_cols, int vec_rows);

void printMat(double **matrix, int n_rows, int n_cols);

void printV(double *vector, int size);

double l2Norm(double* a_vector, int size);

double* substractV(double *v1, double *v2, int size);

/*
Sum of two vectors.
-------------------
Receives v1 and v2.
Returns v1 + v2. 
*/ 
double* addV(double *v1, double *v2, int size);

/*
Sum of two Matrices.
-------------------
Receives m1 and m2 square matrices of the
same size.

Returns m1 + m2. 
*/ 
double** addMat(double **m1, double **m2, int size);
double** substractMat(double **m1, double **m2, int size);
double* vectorTimesConstant(double* vector, double constant, int size);
double** matrixTimesConstant(double** matrix, double constant, int size);
/*
Receives a matrix and an index.
Returns Returns a new 1-D array, containing 
the column of the given matrix located at the given index.
*/
double* getColumn(double** matrix, int index, int size);

/*
Receives a matrix and an index.
Returns a new 1-D array, containing 
the row of the given matrix located at the given index.
*/
double* getRow(double** matrix, int index, int size);

double** matrixTimesMatrix(double** m1, double** m2, int size);