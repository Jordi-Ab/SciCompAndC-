#include <iostream>

// Constant
static const int SIZE = 3; // We are working with 3x3 matrices, and 3x1 vectors.

/*Prototype functions declaration*/

//Functions for working with Vectors:
int dot(int *v1, int *v2);
int* addV(int *v1, int *v2);
int* substractV(int *v1, int *v2);
int* vectorTimesConstant(int* vector, int constant);

//Functions for working with Matrices:
int** allocateMemoryToMatrix(int n_rows, int n_cols);
int** generateA();
int** generateB();
int** addMat(int **m1, int **m2);
int** substractMat(int **m1, int **m2);
int** matrixTimesConstant(int** matrix, int constant);
int** matrixTimesMatrix(int** m1, int** m2);
int* matrixTimesVector(int **matrix, int *vector);
int* getColumn(int** matrix, int index);
int* getRow(int** matrix, int index);

//Functions for printing:
void printV(int *vector);
void printMat(int **matrix);


/*Main Program: */
int main(){
	int u[SIZE] = {1,2,3};
	int v[SIZE] = {6,5,4};

	int** A;
	int** B;

	A = generateA();
	B = generateB();

	int *resta;
	resta = substractV(u,v);
	std::cout << "u - v = " << std::endl;
	printV(resta);
	std::cout << ""<< std::endl;
	delete[] resta;

	int *Au;
	Au = matrixTimesVector(A, u);
	std::cout << "A*u = " << std::endl;
	printV(Au);
	std::cout << ""<< std::endl;

	int *Au_minus_v;
	Au_minus_v = substractV(Au, v);
	std::cout << "A*u - v = " << std::endl;
	printV(Au_minus_v);
	std::cout << ""<< std::endl;

	delete[] Au;
	delete[] Au_minus_v;

	int **restaMat;
	std::cout << "4*A - 3*B = " << std::endl;
	restaMat = substractMat(matrixTimesConstant(A, 4), matrixTimesConstant(B, 3));
	printMat(restaMat);
	std::cout << ""<< std::endl;
	delete[] restaMat;

	int **mmult;
	std::cout << "A*B = " << std::endl;
	mmult = matrixTimesMatrix(A,B);
	printMat(mmult);
	std::cout << ""<< std::endl;
	delete[] mmult;

	delete[] A;
	delete[] B;
	return 0;
}

/*Helper Functions:*/

int** allocateMemoryToMatrix(int n_rows, int n_cols){
	// Function to dynamically allocate memory for a matrix.
	int ** matrix;
	matrix = new int* [n_rows];
	for (int i=0; i<n_rows; i++){
		matrix[i] = new int [n_cols];
	}
	return matrix;
}

int** generateA(){
	int** A;
	A = allocateMemoryToMatrix(SIZE, SIZE);
	A[0][0] = 1; A[0][1] = 5; A[0][2] = 0;
	A[1][0] = 7; A[1][1] = 1; A[1][2] = 2;
	A[2][0] = 0; A[2][1] = 0; A[2][2] = 1;
	return A;
}

int** generateB(){
	int** B;
	B = allocateMemoryToMatrix(SIZE, SIZE);
	B[0][0] = -2; B[0][1] = 0; B[0][2] = 1;
	B[1][0] = 1; B[1][1] = 0; B[1][2] = 0;
	B[2][0] = 4; B[2][1] = 1; B[2][2] = 0;
	return B;
}

/*
Dot Product between two vectors.
-------------------
Receives v1 and v2.
Returns v1[0]*v2[0] + ... + v1[n]*v2[n].
n = SIZE = 3. 
*/ 
int dot(int *v1, int *v2){
	int dot_prod = 0;
	for (int i=0; i<SIZE; i++){
		dot_prod += v1[i] * v2[i];
	}
	return dot_prod;
}

/*
Sum of two vectors.
-------------------
Receives v1 and v2.
Returns v1 + v2. 
*/ 
int* addV(int *v1, int *v2){
	int* result;
	result = new int[SIZE];
	for (int i=0; i<SIZE; i++){
		result[i] = v1[i] + v2[i];
	}
	return result;
}

/*
Sum of two Matrices.
-------------------
Receives m1 and m2.
Returns m1 + m2. 
*/ 
int** addMat(int **m1, int **m2){
	int** result;
	result = new int* [SIZE];
	for (int i=0; i<SIZE; i++){
		result[i] = new int[SIZE];
		result[i] = addV(m1[i], m2[i]);
	}
	return result;
}

int* substractV(int *v1, int *v2){
	int* result;
	result = new int[SIZE];
	for (int i=0; i<SIZE; i++){
		result[i] = v1[i] - v2[i];
	}
	return result;
}

int** substractMat(int **m1, int **m2){
	int** result;
	result = new int* [SIZE];
	for (int i=0; i<SIZE; i++){
		result[i] = new int[SIZE];
		result[i] = substractV(m1[i], m2[i]);
	}
	return result;
}

int* matrixTimesVector(int **matrix, int *vector){
	int* result;
	result = new int[SIZE];
	for (int i=0; i<SIZE; i++){
		result[i] = dot(matrix[i],vector);
	}
	return result;
}

int* vectorTimesConstant(int* vector, int constant){
	int* result;
	result = new int[SIZE];
	for (int i=0; i<SIZE; i++){
		result[i] = vector[i]*constant;
	}
	return result;
}

int** matrixTimesConstant(int** matrix, int constant){
	int** result;
	result = new int* [SIZE];
	for (int i=0; i<SIZE; i++){
		result[i] = new int[SIZE];
		result[i] = vectorTimesConstant(matrix[i], constant);
	}
	return result;
}

int** matrixTimesMatrix(int** m1, int** m2){
	int** result;
	result = new int* [SIZE];
	for (int r=0; r<SIZE; r++){
		int *row = getRow(m1, r);
		result[r] = new int[SIZE];
		for (int c=0; c<SIZE; c++){
			int *col = getColumn(m2, c);
			result[r][c] = dot(row,col);
		}
	}
	return result;
}

/*
Receives a matrix and an index.
Returns Returns a new 1-D array, containing 
the column of the given matrix located at the given index.
*/
int* getColumn(int** matrix, int index){
	int* column = NULL;
	if (index >= SIZE){
		std::cout<<"Error: Index out of range for getColumn @ " << index <<std::endl;	
	} else {
		column = new int[SIZE];
		for (int row=0; row<SIZE; row++){
			column[row] = matrix[row][index];
		}
	}
	return column;
}

/*
Receives a matrix and an index.
Returns a new 1-D array, containing 
the row of the given matrix located at the given index.
*/
int* getRow(int** matrix, int index){
	int* row = NULL;
	if (index >= SIZE){
		std::cout<<"Error: Index out of range for getRow @ " << index <<std::endl;	
	} else {
		row = new int[SIZE];
		row = matrix[index];
	}
	return row;
}

void printV(int *vector){
	for (int i=0; i<SIZE; i++){
		if (vector[i]>=0 && vector[i]<10) std::cout << "| ";
		else std::cout << "|";
		std::cout << vector[i] << "|" << std::endl;
	}
}

void printMat(int **matrix){
	for (int row=0; row < SIZE; row++){
		std::cout << "|";
		for (int col=0; col<SIZE; col++){
			if (matrix[row][col]>=0 && matrix[row][col]<10) std::cout << " ";
			std::cout << matrix[row][col] << " ";
		}
		std::cout << "|" << std::endl;
	}
}