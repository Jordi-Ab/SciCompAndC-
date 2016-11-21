#include <iostream>
#include "InputOutputUtilities.cpp"
#include "LinearAlgebraLibrary.cpp"
#include "matrix_allocation.cpp"
#include "myRandom.cpp"

double** fixedA(int n_rows, int n_cols);
double** bookExample(int n_rows, int n_cols);

int main(){
	int size = 4;
    print("size = ", false);
    print(size);
    double** a_matrix = bookExample(size,size);
    PrintMatrix(size,size, a_matrix, "A");

	double* P = _initP(size);
	double** L = eyeMat(size, size);
	double** U = copyMat(a_matrix, size, size);

	toUpperTriangular(U, P, L, size, size);
	PrintMatrix(size,size, U, "U");
	PrintMatrix(size,size, L, "L");
	PrintVector(size, P, "P");

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