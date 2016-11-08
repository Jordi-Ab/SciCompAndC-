#import <iostream>
#include <stdlib.h>
#include <cmath>
#include <string>
#import "matrix_allocation.cpp"
#import "back_substitution.cpp"
#import "mat_vec_prod.cpp"
#import "solve_ax_eq_b.cpp"
#import "mat_vec_prod.cpp"

/*Function prototype declarations, and explanations*/

/*
Function: printMat
Usage: printMat(a_matrix, 3, 3)
-----------------------------------
Outputs a string representation of a n_rows x n_cols
matrix object to the console window.
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

# This is a private function and shouldn't be used
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

// Computes the l2-norm of a vector.
double l2Norm(double* a_vector, int size); 
// Substracts two vectors.
double* substractV(double *v1, double *v2, int size); 
// Creates a random matrix having n_rows x n_cols.
double** createRandomMatrix(int n_rows, int n_cols); 
// Creates a random vector of the given size
double* createRandomVector(int size); 
// Initialize the random seed.
static void initRandomSeed(); 
// Returns a random Integer number between 2 and 9.
int myRandomInteger();
// Returns a random Integer number between low and high.
int randomInteger(int low, int high);
 /*
 Comments about why I use two different random Integer
 functions are below, on the functions themselves,
 read them if interested.
 */

// Returns a random Double precision number between low and high.
double randomReal(double low, double high); 
// Tests the code for a random matrix and a random vector of random size.
void testWithRandomInputs();

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
    freeMatrixMemory(n_rows, A1);
    delete[] x1;
    delete[] Ax1;
	delete[] residual1;

	// Running code for the second matrix in the excercise sheet.
	double** A2 = _generateMatrix(2, n_rows, n_cols); // generate the second matrix in the sheet.
	double* x2 = solveAxEqB(A2, b, n_rows);
	std::cout << "x for System 2: " << std::endl;
	printV(x2, n_rows); // print the resulting x
	double* Ax2 = matrixTimesVector(A2, x2, n_rows, n_cols, n_rows); // multiply A times x.
    double* residual2 = substractV(b, Ax2, n_rows);
	std::cout << "l2-norm of b-Ax = " << l2Norm(residual2, n_rows)<<std::endl;
	std::cout << " " << std::endl;
    freeMatrixMemory(n_rows, A2);
    delete[] x2;
	delete[] Ax2;
	delete[] residual2;
	

	//Uncomment next function if you want to test the code with random inputs.
	
    //testWithRandomInputs();
	
    return 0;
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
	double norm = 0.0;
    for (int i=0; i<size; i++){
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

/*All next section are functions to test the code with
random inputs*/

void testWithRandomInputs(){
	std::cout << " " << std::endl;
	std::cout << "Testing with random inputs:" << std::endl;
    int size = myRandomInteger(); // I use myRandomInteger just for the inital size.
	std::cout << "Size of the system:" << size << std::endl;

	double** a_matrix = createRandomMatrix(size, size);
	std::cout << "Random Matrix:" << std::endl;
	printMat(a_matrix, size, size);
	double* a_vector = createRandomVector(size);
	std::cout << "Random Vector:" << std::endl;
	printV(a_vector, size);
	double* sol = solveAxEqB(a_matrix, a_vector, size);
	std::cout << "Solution:" << std::endl;
	printV(sol, size);

	if (sol != NULL){
		double* Ax = matrixTimesVector(a_matrix, sol, size, size, size); // multiply A times x.
		double* residual = substractV(a_vector, Ax, size);
		std::cout << "l2-norm of b-Ax = " << l2Norm(residual, size)<<std::endl;
		std::cout << " " << std::endl;
        delete[] Ax;
        delete[] residual;
	}
    
    freeMatrixMemory(size, a_matrix);
    delete[] a_vector;
    delete[] sol;
    
    
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
		//int entry = randomInteger(-9, 9); // For random vectors of integers
		double entry = randomReal(-9.9, 9.9); // For random vectors of double precision
		rand_vec[i] = /*(double)*/entry; // Parse to double when using the integer entries.
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

int myRandomInteger(){
    /*
     I created this function because the conventional way of
     creating random Integers, which is in the randomInteger
     function, is biased towards the lowest value of the range.
     When you run the program, the first generated number is
     almost always the lowest value on the range. 
     In this program the first time I called randomInteger 
     was to decide the size of the system to be solved, so almost
     always it returned a 2x2 system.
     So I hacked a function that the first time you run it returns
     a truly random Integer between 2 and 9.
     
     #Its not the most efficient way of creating a non biased 
     random Integer between an interval, but does the job 
     for this excercise.
    */
    initRandomSeed();
    int r = rand();
    std::string str = std::to_string(r);
    char last_value = str[str.length()-1];
    int l = last_value - 48;
    
    if (l <= 1) l+=2;
    
    return l;
    /*
     Basically, it chooses the last integer in the number generated by
     rand(). The problem of the bias towards the lowest value of the 
     interval is that rand() returns very large numbers, so the first
     numbers of rand() almost never change, so when doing all the
     manipulations to map the rand() to an integer on an interval, it
     almost always returned the lowest value. So instead of that I worked
     with the last integer of rand(), which do varies very much every time
     you run it for the first time.
    */
}
