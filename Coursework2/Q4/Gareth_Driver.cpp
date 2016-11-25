#include "Chebyshev.cpp"
#include "VecsAndMats.cpp"
#include "InputOutputUtilities.cpp"
#include "matrix_allocation.cpp"
#include "LinearAlgebraLibrary.cpp"

int main (int argc, char* argv[])
{
    //Allocating an array to store the different n values.
    int n;
    n=3;
    
    //==========================================================================================
    //In this section, D is calculated and used to get D^2
    //Allocating the x vector.
    double* x;
    x = new double [n+1];
    
    //Allocating the D Matrix.
    double** D;
    D = allocateMatrixMemory(n+1, n+1);
    
    //Using the followinf function to find the D matrix.
    ChebyshevDifferentiationMatrix(n, x, D);
    PrintMatrix(n+1, n+1, D, "D");    //Test Print
    
    delete x; //No longer needed. -> Giordi comment: change to delete[] x;
    
    //The following function computes D^2, which is required for the computation.
    double** K = matrixTimesMatrix(D, D, n+1);
    PrintMatrix(n+1, n+1, K, "D^2");  //Test Print
    
    double** D2;
    D2 = allocateMatrixMemory(n-1, n-1);
    
    for (int i=1; i<n; i++)
    {
        for (int j=1; j<n; j++)
        {
            D2[i-1][j-1]=K[i][j];
        }
    }
    
    freeMatrixMemory(n+1, K); //No longer required
    
    PrintMatrix(n-1, n-1, D2, "D2");  //Test Print

    //Allocation of memory for matrix L
    double** L;
    L = allocateMatrixMemory(n-1, n-1);
    
    //Allocation of memory for matrix U
    double** U;
    U = freeMatrixMemory(n-1, n-1);
    
    //Allocation of memory for the permutation vector
    int* pi;
    pi = new int [n-1];
    
    PLUDecomposition(n-1, D2, L, U, pi);
    
    //PrintMatrix(n-1, n-1, L, "L");
    //PrintMatrix(n-1, n-1, U, "U");
    
    deallocate_matrix(n-1, D2);
}