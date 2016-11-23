#include <iostream>
#include "InputOutputUtilities.cpp"
#include "LinearAlgebraLibrary.cpp"
#include "matrix_allocation.cpp"
#include "myRandom.cpp"
#include "VecsAndMats.hpp"

double** fixedA(int n_rows, int n_cols);
double** bookExample(int n_rows, int n_cols);
double** andreasA(int n_rows, int n_cols);

int main(){
	int size = 4;
    print("size = ", false);
    print(size);
    double** A = andreasA(size,size);
    PrintMatrix(size,size, A, "A");

	int* pi = new int[size];
	double** L = allocateMatrixMemory(size, size);
	double** U = allocateMatrixMemory(size, size);

	PLUDecomposition(size, A, L, U, pi);
	PrintMatrix(size,size, U, "U");
	PrintMatrix(size,size, L, "L");
	PrintVector(size, pi, "P");

	PermuteMatrix(size, pi, A);
    //double** PA = matrixTimesMatrix(fullP, A, size);
    PrintMatrix(size,size, A, "PA");

    double** LU = matrixTimesMatrix(L, U, size);
    PrintMatrix(size,size, LU, "LU");

    double** residual = substractMat(A, LU, size);
    PrintMatrix(size,size, residual, "(PA - LU)");

    return 0;
}

double** fixedA(int n_rows, int n_cols){
    /*
     * Create a fixed matrix for example.
     */
    setRandomSeed(235);
    double** A = allocateMatrixMemory(n_rows, n_cols);
    for (int i=0; i<n_rows; i++){
        for (int j=0; j<n_cols; j++){
            double entry = std::round(5*randomReal(-9.9, 9.9));
            A[i][j] = entry;
        }
    }
    A[0][0] = 0;
    A[2][1] = 17;
    A[0][2] = 19;
    PrintMatrix(4,4, A, "a_matrix");
    return A;
}

double** bookExample(int n_rows, int n_cols){
    /*
     * Create a fixed matrix for example.
     */

    double** A = allocateMatrixMemory(n_rows, n_cols);
    
    A[0][0] = 2;A[0][1] = 1;A[0][2] = 1;A[0][3] = 0;
    A[1][0] = 4;A[1][1] = 3;A[1][2] = 3;A[1][3] = 1;
    A[2][0] = 8;A[2][1] = 7;A[2][2] = 9;A[2][3] = 5;
    A[3][0] = 6;A[3][1] = 7;A[3][2] = 9;A[3][3] = 8;
    return A;
}

double** andreasA(int n_rows, int n_cols){
    /*
     * Create a fixed matrix for example.
     */

    double** A = allocateMatrixMemory(n_rows, n_cols);
    
    A[0][0] =  0;A[0][1] =  4;A[0][2] =  19;A[0][3] = -7;
    A[1][0] = -1;A[1][1] = -2;A[1][2] = -10;A[1][3] = -0;
    A[2][0] =  1;A[2][1] = 17;A[2][2] =   1;A[2][3] = -4;
    A[3][0] = -5;A[3][1] = -8;A[3][2] =  -6;A[3][3] = -2;
    return A;
}