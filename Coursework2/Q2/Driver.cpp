#include <iostream>
#include "InputOutputUtilities.cpp"
#include "LinearAlgebraLibrary.cpp"
#include "matrix_allocation.cpp"
#include "myRandom.cpp"

double** fixedA();

int main(){
    double** a_matrix = fixedA();
    PrintMatrix(4,4, a_matrix, "a_matrix");
    return 0;
}

double** fixedA(){
    /*
     * Create a fixed matrix for example.
     */
    int n_rows = 4;
    int n_cols = 4;
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
    return A;
}
