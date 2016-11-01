#import <iostream>
#import "matrix_allocation.cpp"
#import "back_substitution.cpp"
#import "mat_vec_prod.cpp"
#import "solve_ax_eq_b.cpp"


/*
Template for descriptions:
Function: 
Usage: 
-----------------------------------
(brief description)
*/



/*Function prototype declarations, and explanations*/

/*
Function: printMat
Usage: printMat(a_matrix, 3, 3)
-----------------------------------
Outputs a string representation of a n_rows x n_cols matrix
object to the console window.
*/
void printMat(double **matrix, int n_rows, int n_cols);

void printV(double *vector, int size);

/*
Function: _generateMatrix
	#Intended for internal usage only.
Usage: double** A = _generateMatrix(1);

* This is a private function and shouldn't be used
with numbers that are not 1 or 2.
-----------------------------------
Receives a number that corresponds to the matrix
in the excercise sheet.
n = 1 Generates the first matrix of the excercise sheet.
Nameley:
|  2  1  1  0  |
|  4  3  3  1  |
|  8  7  9  5  |
|  6  7  9  8  |
n = 2 Generates the second matrix of the excercise sheet.
(Any other value for n will generate the second matrix of the excercise sheet.)
*/
double** _generateMatrix(int n, int n_rows, int n_cols);


/*--------Main Program-------*/
int main(){

	int n_rows = 4; // number of rows of the matrices we are working with
	int n_cols = 4; // number of columns of the matrices we are working with

	double** A1 = _generateMatrix(1, n_rows, n_cols);
	//printMat(A1, n_rows, n_cols);

	double** A2 = _generateMatrix(2, n_rows, n_cols);
	//printMat(A2, n_rows, n_cols);

	double b[4] = {2,4,10,8};

	double* x1 = solveAxEqB(A1, b, n_rows);
	std::cout << "x for System 1: " << std::endl;
	printV(x1, n_rows);

	double* x2 = solveAxEqB(A2, b, n_rows);
	std::cout << "x for System 2: " << std::endl;
	printV(x2, n_rows);
	

	return 0;
}

void printMat(double **matrix, int n_rows, int n_cols){
	for (int row=0; row < n_rows; row++){
		std::cout << "|";
		for (int col=0; col<n_cols; col++){
			if (_isAlmostZero(matrix[row][col])) std::cout << 0 << " " << std::endl;
			else if (matrix[row][col]>0 && matrix[row][col]<10) std::cout << " ";
			else std::cout << matrix[row][col] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

void printV(double *vector, int size){
	for (int i=0; i<size; i++){
		if (vector[i]>=0 && vector[i]<10) std::cout << "| ";
		else std::cout << "|";
		if (_isAlmostZero(vector[i])) std::cout << 0 << "|" << std::endl;
		else std::cout << vector[i] << "|" << std::endl;
	}
}

double** _generateMatrix(int n, int n_rows, int n_cols){
	// This is a private function and shouldn't be used with numbers that are not 1 or 2.
	double** A;
	A = allocateMatrixMemory(n_rows, n_cols);

	// The only thing that differs between the first and the second matrix is the first element.
	double f_e; // A variable for the first element.
	if (n==1) f_e = 2.0; 
	else f_e = 0.0;

	A[0][0] = f_e; A[0][1] = 1.0; A[0][2] = 1.0; A[0][3] = 0.0;
	A[1][0] = 4.0; A[1][1] = 3.0; A[1][2] = 3.0; A[1][3] = 1.0;
	A[2][0] = 8.0; A[2][1] = 7.0; A[2][2] = 9.0; A[2][3] = 5.0;
	A[3][0] = 6.0; A[3][1] = 7.0; A[3][2] = 9.0; A[3][3] = 8.0;
	return A;
}