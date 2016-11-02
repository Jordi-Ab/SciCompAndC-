#import <iostream>
#include <stdlib.h>
#include <cmath>
#import "matrix_allocation.cpp"
#import "back_substitution.cpp"
#import "mat_vec_prod.cpp"
#import "solve_ax_eq_b.cpp"
#import "mat_vec_prod.cpp"


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

/*
Function: printV
Usage: printV(a_vector, 3)
-----------------------------------
Outputs a string representation of a "size" vector
object to the console window.
*/
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

/*Functions to test the code*/
double l2Norm(double* a_vector, int size); // Computes the l2-norm of a vector.
double* substractV(double *v1, double *v2, int size); // Substracts two vectors.
double** createRandomMatrix(int n_rows, int n_cols); // Creates a random matrix having n_rows x n_cols.
double* createRandomVector(int size); // Creates a random vector of the given size
static void initRandomSeed(); // Initialize the random seed.
int randomInteger(int low, int high); // Returns a random Integer number between low and high.
double randomReal(double low, double high); // Returns a random Double precision number between low and high.
void testWithRandomInputs(); // Tests the code for a random matrix and a random vector of random size.

/*--------Main Program-------*/
int main(){

	int n_rows = 4; // number of rows of the matrices we are working with
	int n_cols = 4; // number of columns of the matrices we are working with

	double b[4] = {2,4,10,8};

	// Running code for the first matrix in the excercise sheet.
	double** A1 = _generateMatrix(1, n_rows, n_cols); // generate the first matrix in the sheet.
	double* x1 = solveAxEqB(A1, b, n_rows);
	std::cout << "x for System 1: " << std::endl;
	printV(x1, n_rows); // print the resulting x
	double* Ax1 = matrixTimesVector(A1, x1, n_rows, n_cols, n_rows); // multiply A times x.
	double* residual1 = substractV(b, Ax1, n_rows); // compute the residual vector b - Ax.
	std::cout << "l2-norm of b-Ax = " << l2Norm(residual1, n_rows)<<std::endl; 
	std::cout << " " << std::endl;
	delete[] Ax1;
	delete[] residual1;
	delete[] A1;
	delete[] x1;

	// Running code for the second matrix in the excercise sheet.
	double** A2 = _generateMatrix(2, n_rows, n_cols); // generate the second matrix in the sheet.
	double* x2 = solveAxEqB(A2, b, n_rows);
	std::cout << "x for System 2: " << std::endl;
	printV(x2, n_rows); // print the resulting x
	double* Ax2 = matrixTimesVector(A2, x2, n_rows, n_cols, n_rows); // multiply A times x.
	double* residual2 = substractV(b, Ax2, n_rows);
	std::cout << "l2-norm of b-Ax = " << l2Norm(residual2, n_rows)<<std::endl; 
	std::cout << " " << std::endl;
	delete[] Ax2;
	delete[] residual2;
	delete[] A2;
	delete[] x2;

	//Uncomment next function if you want to test the code with random inputs.
	//testWithRandomInputs();
	return 0;
}

void testWithRandomInputs(){
	std::cout << " " << std::endl;
	std::cout << "Testing with random inputs:" << std::endl;
	int rand_size = randomInteger(1, 9);
	std::cout << "Size of the system:" << rand_size << std::endl;

	double** a_matrix = createRandomMatrix(rand_size, rand_size);
	std::cout << "Random Matrix:" << std::endl;
	printMat(a_matrix, rand_size, rand_size);
	double* a_vector = createRandomVector(rand_size);
	std::cout << "Random Vector:" << std::endl;
	printV(a_vector, rand_size);
	double* sol = solveAxEqB(a_matrix, a_vector, rand_size);
	std::cout << "Solution:" << std::endl;
	printV(sol, rand_size);

	if (sol != NULL){
		double* Ax = matrixTimesVector(a_matrix, sol, rand_size, rand_size, rand_size); // multiply A times x.
		double* residual = substractV(a_vector, Ax, rand_size);
		std::cout << "l2-norm of b-Ax = " << l2Norm(residual, rand_size)<<std::endl; 
		std::cout << " " << std::endl;
	}
}

void printMat(double **matrix, int n_rows, int n_cols){
	for (int row=0; row < n_rows; row++){
		std::cout << "|";
		for (int col=0; col<n_cols; col++){
			if (matrix[row][col]>=0 && matrix[row][col]<10) std::cout << " ";
			std::cout << matrix[row][col] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

void printV(double *vector, int size){
	if(vector == NULL){
		std::cout << "NULL vector" << std::endl;
	}else{
		for (int i=0; i<size; i++){
			if (vector[i]>=0 && vector[i]<10) std::cout << "| ";
			else std::cout << "|";
			if (isAlmostZero(vector[i])) std::cout << 0 << "|" << std::endl;
			else std::cout << vector[i] << "|" << std::endl;
		}
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

double l2Norm(double* a_vector, int size){
	int norm = 0.0;
    for (int i=1; i<size; i++){
        norm += pow(a_vector[i],2.0);
    }
    return sqrt(norm);
}

double* substractV(double *v1, double *v2, int size){
	double* result;
	result = new double[size];
	for (int i=0; i<size; i++){
		result[i] = v1[i] - v2[i];
	}
	return result;
}

double** createRandomMatrix(int n_rows, int n_cols){
	double** rand_matrix = allocateMatrixMemory(n_rows,n_cols);
	for (int i=0; i<n_rows; i++){
		for (int j=0; j<n_cols; j++){
			int entry = randomInteger(-9, 9);
			rand_matrix[i][j] = (double)entry; 
		}
	}
	return rand_matrix;
}

double* createRandomVector(int size){
	double* rand_vec;
	rand_vec = new double[size];
	for (int i=0; i<size; i++){
		//int entry = randomInteger(-9, 9);
		double entry = randomReal(-9.9, 9.9);
		rand_vec[i] = /*(double)*/entry; 
	}
	return rand_vec;
}

static void initRandomSeed() {
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(NULL)));
        initialized = true;
    }
}

int randomInteger(int low, int high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (double(high) - low + 1);
    return int(floor(low + s));
}

double randomReal(double low, double high) {
	initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (high - low);
    return low + s;
}