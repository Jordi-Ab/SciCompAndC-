#import <iostream>
#include <stdlib.h>
#include <cmath>
#import "matrix_allocation.cpp"
#import "back_substitution.cpp"
#import "mat_vec_prod.cpp"
#import "row_pivoting.cpp"
#import "solve_ax_eq_b.cpp"

static void initRandomSeed();

void printV(double *vector, int size);
void printMat(double **matrix, int n_rows, int n_cols);
double** createRandomUpperT(int n_rows, int n_cols);
double** createRandomMatrix(int n_rows, int n_cols);
double randomReal(double low, double high);
int randomInteger(int low, int high);
double* createRandomVector(int size);
double** augmentMatrix(double** matrix, double* vector, int mat_rows, int mat_cols);
double l2Norm(double* a_vector, int size);
double* substractV(double *v1, double *v2, int size);
double** aSquareMatrix(int size);
void testBackSubstitution();
void testRowPivoting();
//bool _isAlmostZero(double number);


int main(){
	//testBackSubstitution();
	testRowPivoting();
	std::cout << isAlmostZero(-0.01, 1e-6) <<std::endl;
	std::cout << (0.01 <= 1e-6) << std::endl;
	double** a_matrix = createRandomMatrix(6,6);
	printMat(a_matrix, 6,6);
}

void testRowPivoting(){
	int size = 4;
	double** a_matrix = aSquareMatrix(size);
	std::cout << "Matrix:" << std::endl;
	printMat(a_matrix, size, size);
	std::cout << " " << std::endl;
	for(int i=0;i<size;i++){
		int pivot_index = findPivot(a_matrix, i, size);
		std::cout<<"For column "<<i<<", pivot is located at row "<< pivot_index+1<<std::endl;
		swapRows(a_matrix, i, pivot_index);
		std::cout << "Resulting Matrix:" << std::endl;
		printMat(a_matrix, size, size);
	}
}

void testAxEqb(){
	
}

/*bool _isAlmostZero(double number){
	if (number < 0){ // I make cases for negative number because abs(number) truncates the number.
		return (number >= -1.0e-10);
	}else{
		return (number <= 1.0e-10);
	}
}*/

void testBackSubstitution(){
	double** upper_t = createRandomUpperT(4,4);
	std::cout << "Random upper T: " << std::endl;
	printMat(upper_t,4,4);

	double** randM = createRandomMatrix(4,4);
	//printMat(randM,4,4);

	double* a_vec = createRandomVector(4);
	std::cout << "Random vector x: " << std::endl;
	printV(a_vec, 4);

	double* b = matrixTimesVector(upper_t, a_vec, 4, 4, 4);
	std::cout << "Ax = " << std::endl;
	printV(b, 4);

	std::cout << "" << std::endl;
	std::cout << "Now find x for A and b. " << std::endl;
	std::cout << "" << std::endl;
	double** aug_mat = augmentMatrix(upper_t, b,4,4);
	std::cout << "Augmented Matrix: " << std::endl;
	printMat(aug_mat,4,5);

	double* computed_x = backSubstitution(aug_mat, 4,5);
	printV(computed_x, 4);

	double norm = l2Norm(substractV(a_vec,computed_x,4),4);
	std::cout << "Difference = "<< norm << std::endl;	
}

double** aSquareMatrix(int size){
	double** A = allocateMatrixMemory(size, size);
	A[0][0] = 0; A[0][1] = 2; A[0][2] = -1; A[0][3] = 6;
	A[1][0] = 1; A[1][1] = 0; A[1][2] = 2; A[1][3] = 1;
	A[2][0] = -1; A[2][1] = 0; A[2][2] = 3; A[2][3] = -5;
	A[3][0] = 2; A[3][1] = 1; A[3][2] = 0; A[3][3] = 2;
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

double** augmentMatrix(double** matrix, double* vector,int mat_rows, int mat_cols){
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

void printV(double *vector, int size){
	for (int i=0; i<size; i++){
		if (vector[i]>=0 && vector[i]<10) std::cout << "| ";
		else std::cout << "|";
		std::cout << vector[i] << "|" << std::endl;
	}
}

double** createRandomUpperT(int n_rows, int n_cols){
	double** rand_matrix = allocateMatrixMemory(n_rows,n_cols);
	for (int i=0; i<n_rows; i++){
		for (int j=0; j<n_cols; j++){
			double entry;
			if(j<i) entry = 0;
			else entry = randomReal(-9.9, 9.9);
			rand_matrix[i][j] = entry; 
		}
	}
	return rand_matrix;
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

/*
A[0][0] = 1.0; A[0][1] = 2.0; A[0][2] = -3.0; A[0][3] = -6.0; A[0][4] = 2.0;
	A[1][0] = 0.0; A[1][1] = -8.0; A[1][2] = 2.0; A[1][3] = 1.0; A[1][4] = -3.0;
	A[2][0] = 0.0; A[2][1] = 0.0; A[2][2] = 3.0; A[2][3] = -5.0; A[2][4] = 1.0;
	A[3][0] = 0.0; A[3][1] = 0.0; A[3][2] = 0.0; A[3][3] = 2.0; A[3][4] = -1.0;
*/