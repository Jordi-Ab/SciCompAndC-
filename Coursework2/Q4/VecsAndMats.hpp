#include <iostream>
#include <cmath>

/*
Function: allocateMatrixMemory
---------------------------------------------
Saves space in the computer's memory to hold a
matrix of n_rows by n_cols size, and returns a new
pointer to this space.
*/
double** allocateMatrixMemory(int n_rows, int n_cols);

/*
Function: freeMatrixMemory
--------------------------------------------------
Receives the number of rows of the matrix, and the
matrix itself for which you want to free the memory space. 
Deallocates the memory used by the given matrix.
*/
void freeMatrixMemory(int n_rows, double** matrix);

/*
Function: dot
-------------------
Computes the Dot Product between two vectors.
Receives two vectors. "v1" and "v2", and the size of this vectors.

v1[0]*v2[0] + ... + v1[n]*v2[n].
 
#Assumes both vectors have the same size.
*/ 
double dot(double *v1, double *v2, int size);

/*
Function: matrixTimesVector
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

/*
Function: printMat
-------------------
Prints a given matrix of given shape in the console window.
*/ 
void printMat(double **matrix, int n_rows, int n_cols);

/*
Function: printV
-------------------
Prints a given vector of given size in the console window.
*/ 
void printV(double *vector, int size);

/*
Function: l2Norm
-------------------
Computes the l2 norm of the given vector.
# Size of the vector must be provided.
*/
double l2Norm(double* a_vector, int size);

/*
Function: infinityNorm
-------------------
Computes the infinity norm of the given vector.
# Size of the vector must be provided.
*/
double infinityNorm(double* a_vector, int size);

/*
Function: addV
-------------------
Sum of two vectors.
Receives v1 and v2.
Returns a new vector containing the result of
v1 + v2. 
*/ 
double* addV(double *v1, double *v2, int size);

/*
Function: addMat
-------------------
Sum of two Matrices.
Receives m1 and m2 square matrices of the
same size.

Returns a new matrix containing the result of
m1 + m2. 
*/ 
double** addMat(double **m1, double **m2, int size);

/*
Function: substractV
-------------------
Substracts each element of vector2 from vector1.
i.e. v1 - v2
Returns a new vector that holds the result.

# Size of the vector must be provided. Assumes both
vectors have the same size.
*/
double* substractV(double *v1, double *v2, int size);

/*
Function: substractMat
-------------------
Substracts each element of matrix2 from matrix1.
i.e. m1 - m2
Returns a new vector that holds the result.

# Size of the matrix must be provided. Assumes both
mstrices are square and have the same size.
*/
double** substractMat(double **m1, double **m2, int size);

/*
Function: vectorTimesConstant
-------------------
Multiplies each element of a vector times a constant.
Returns a new vector holding the result.

# Note to me: Consider making this function a void to mutate
the vector instead of returning a new pointer.
*/
double* vectorTimesConstant(double* vector, double constant, int size);

/*
Function: matrixTimesConstant
-------------------
Multiplies each element of a matrix times a constant.
Returns a new matrix holding the result.

# Note to me: Consider making this function a void to mutate
the matrix instead of returning a new pointer.
*/
double** matrixTimesConstant(double** matrix, double constant, int size);

/*
Function: getColumn
-------------------
Receives a matrix and an index.
Returns a new 1-D array, containing 
the column of the given matrix located at the given index.
*/
double* getColumn(double** matrix, int index, int size);

/*
Function: getColumn
-------------------
Receives a matrix and an index.
Returns a new 1-D array, containing 
the row of the given matrix located at the given index.

#Note to me: instead of returning a new pointer, why not returning
the actual pointer to the row? Then you could overwrite it in some way.
*/
double* getRow(double** matrix, int index, int size);

/*
Function: matrixTimesMatrix
-------------------
Matrix Matrix multiplication.
Returns a new 2-D pointer, containing 
the result of m1*m2

# Size of the matrix must be provided. 
# Assumes both matrices are square and have the same size.
*/
double** matrixTimesMatrix(double** m1, double** m2, int size);

/*
Function: isVectorAlmostZero
-------------------
Returns true if a vector is almost zero.
i.e. All its elements are less that a given
tolerance.
# Default tolerance is 1e-8.
*/
bool isVectorAlmostZero(double* vector, int size,
                        double error_tol);

/*
Function: isAlmostZero
-------------------
Returns true if a given number is almost zero.
i.e. Is less that a given tolerance.
# Default tolerance is 1e-8.
*/
bool isAlmostZero(double number, double error_tol);
