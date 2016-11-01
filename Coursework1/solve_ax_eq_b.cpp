
#import "row_pivoting.cpp"

/*
Function: _augmentMatrix
	*Intended only for internal usage of solveAxEqB.
Usage: double** aug_mat = _augmentMatrix(a_mat, a_vec, n_mat_rows, n_mat_cols)
--------------------------------------------------------
Receives a matrix, a vector, the number of rows in the matrix
and the number of columns in the matrix.

*The given vector must have the same number of rows as the given matrix.
Else, it will cut the vector to the rows of the matrix.

Returns a new matrix, which will be the augmented version of the given
matrix with the given vector. That is, it adds the vector as the last 
column of the matrix.

i.e.

double** aug_mat = _augmentMatrix(A, b, 4, 4)

    |  1  2 -3 -6 |      | 2 |                  |  1  2 -3 -6  2 |
A = |  0 -8  2  1 |, b = |-3 |, then: aug_mat = |  0 -8  2  1 -3 |
    |  0  0  3 -5 |      | 1 |                  |  0  0  3 -5  1 |
    |  0  0  3 -5 |      | 1 |                  |  0  0  3 -5  1 |
*/
double** _augmentMatrix(double** matrix, double* vector,int mat_rows, int mat_cols);

/*
Function: _eliminate
	*Intended only for internal usage of solveAxEqB.
Usage: double* new_row = _eliminate(a_row, another_row, factor, size);
-----------------------------------------------------
Receives:
	."row1" -> First row, a vector.
	."row2" -> Second row, a vector.
	."factor" -> an integer
	."size" -> number of entries in both vectors.

Performs the elimination step between two rows.
Returns: a new vector containing the result of the elimination step.

Elimination step consists of: new_row = row1 - (factor*row2).
This will zero out the first entry of row 1.
*/
double* _eliminate(double *row1, double *row2, double factor, int vecs_size);

/*
Function: _eliminateRows
	*Intended only for internal usage of solveAxEqB.
Usage: _eliminateRows(a_matrix, current_row, size);
-----------------------------------------------------
Receives:
	."matrix" -> Matrix you want to perform elimination.
	."position" -> Current pivot position. Working with square matrices,
	so position has coordinates (position, position) inside the matrix.
	."size" -> size of the matrix. Working with square matrices, so
	matrix has dimensions size x size.

Performs the elimination step on each subsequent row from
"position" downwards, leaving the column fixed.

Has no return value, so it mutates the given matrix.

*Assumes the pivot is in its correct place, so it will take the
pivot at (position, position).
*/
void _eliminateRowsUnderneath(double** matrix, int position, int n_rows, int n_cols);

/*
Function: _isAlmostZero
	*Intended only for internal usage of solveAxEqB.
Usage: bool flag = _isAlmostZero(a_number);
-----------------------------------------------------
Receives a number.
Returns true if the given number is a computer zero.
i.e. Number is less that 1e-10
*/
bool _isAlmostZero(double number);

bool _isVectorAlmostZero(double* vector, int size);

/*------------Main Function of this script.----------------*/

/*
Function: solveAxEqB
Usage: double* x = solveAxEqB(a_matrix, a_vector, size);
-----------------------------------------------------
Finds x for the Linear system, represented in Matrix 
vector form. Ax = b.

A is a size x size matrix,
b is a size x 1 vector.

Returns x, a vector -> solution of the system

Performs this by Gaussian Elimination with Partial Pivoting.

*/

void toUpperTriangular(double** matrix, int n_rows, int n_cols);

double* solveAxEqB(double** A, double* b, int size){
	// Remember to add the case when infinite many solutions.
	double* result; 
	double** aug_A = _augmentMatrix(A, b, size, size);
	toUpperTriangular(aug_A, size, size+1); // size+1 because we are working with the augmented matrix, which now has size+1 columns.
	result = backSubstitution(aug_A, size, size+1);
	return result;
}

void toUpperTriangular(double** matrix, int n_rows, int n_cols){
	for(int row=0; row<n_rows; row++){
		int pivot_index = findPivot(matrix, row, n_rows);// findPivot function is in "row_pivoting.cpp"
		if (row != pivot_index) swapRows(matrix, row, pivot_index); // swapRows function is in "row_pivoting.cpp"
		_eliminateRowsUnderneath(matrix, row, n_rows, n_cols);
	}
}


/*------------------Helper Functions----------------------------*/
void _eliminateRowsUnderneath(double** matrix, int position, int n_rows, int n_cols){
	double* pivot_row = matrix[position];
	double pivot_entry = pivot_row[position];
	for (int row=position+1; row<n_rows; row++){
		double* next_row = matrix[row];
		double first_element = next_row[position];
		if (!_isAlmostZero(first_element)){ // If the element is zero, or almost zero, there's no need to eliminate the row.
			double factor = first_element/pivot_entry; 
			double* new_row = _eliminate(next_row, pivot_row, factor, n_cols); 
			// if new_row is a row of pure zeros, then matrix is not invertible, or has infinite solutions.
			matrix[row] = new_row; // Overwite the current row with the result of the elimination step.
		}
	}
}

bool _isAlmostZero(double number){
	if (number < 0){ // I make cases for negative number because abs(number) rounds the number.
		return (number >= -1.0e-10);
	}else{
		return (number <= 1.0e-10);
	}
}

bool _isVectorAlmostZero(double* vector, int size){
	bool value = true;
	for (int i=0; i<size; i++){
		entry = vector[entry];
		// If any of its entries is not a computer zero, return false i.e. not a zeros vector.
		if(!_isAlmostZero(entry)) return false; 
	}
	return value; // After iterating through all entries, all of them are computer zeros.
}

double** _augmentMatrix(double** matrix, double* vector,int mat_rows, int mat_cols){
	double** result = allocateMatrixMemory(mat_rows,mat_cols+1);
	for (int row=0; row<mat_rows; row++){
		for (int col=0; col<=mat_cols; col++){
			double entry;
			if (col == mat_cols) entry = vector[row];
			else entry = matrix[row][col];
			result[row][col] = entry;
		}
	}
	return result;
}

double* _eliminate(double *row1, double *row2, double factor, int vecs_size){
	double* result;
	result = new double[vecs_size];
	for (int i=0; i<vecs_size; i++){
		result[i] = row1[i] - factor*row2[i];
	}
	return result;
}

