//==========================================================================================
//Gareth Calvert - 4265464 - University of Nottingham - 2016/2017
//==========================================================================================

#include <iostream>
#include <fstream>
#include <cmath>
#include "Chebyshev.cpp"
#include "mat_mat_prod.cpp"
#include "mat_row_prod.cpp"
#include "matrix_allocation.cpp"
#include "InputOutputUtilities.cpp"
//#include "LinearAlgebraLibrary.cpp"
#include "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework2/Q4/LinearAlgebraLibrary.cpp"
#include "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework2/Q4/VecsAndMats.cpp"
//==========================================================================================
//Function interfaces for funtions not stored in this file, but called in main.
void ChebyshevDifferentiationMatrix(int n, double* x, double** D);
void mat_row_prod(int n, double **D, double *u);
double **allocate_matrix(int n, int m);
void deallocate_matrix(int n, double **A);
void mat_mat_prod(int n, double** A, double** B);
void PLUDecomposition(int n, double** A, double** L, double** U, int* pi);
void SolveLinearSystem(int n, double** L, double** U, int* pi, double* b);
//==========================================================================================
void PrintMatrix(int n, int m, double** A, std::string matrixName);
void PrintVector(int n, double* v, std::string vectorName);
void PrintVector(int n, int* v, std::string vectorName);
void SaveVectorToFile(int n, double* v, std::string fileName);
//==========================================================================================
double* copyVector(double* a_vector, int n);
int main (int argc, char* argv[])
{
    //Allocating an array to store the different n values.
    int n;
    n=5;
    
    //==========================================================================================
    //In this section, D is calculated and used to get D^2
    //Allocating the x vector.
    double* x;
    x = new double [n+1];
    
    //Allocating the D Matrix.
    double** D;
    D = allocate_matrix(n+1, n+1);
    
    //Using the followinf function to find the D matrix.
    ChebyshevDifferentiationMatrix(n, x, D);
    //PrintMatrix(n+1, n+1, D, "D");    //Test Print
    
    delete x; //No longer needed.
    
    //The following function computes D^2, which is required for the computation.
    mat_mat_prod(n+1, D, D);
    //PrintMatrix(n+1, n+1, D, "D^2");  //Test Print
    
    double** D2;
    D2 = allocate_matrix(n-1, n-1);
    
    for (int i=1; i<n; i++)
    {
        for (int j=1; j<n; j++)
        {
            D2[i-1][j-1]=D[i][j];
        }
    }
    
    deallocate_matrix(n+1, D); //No longer required
    
    //PrintMatrix(n-1, n-1, D2, "D2");  //Test Print
    
    //==========================================================================================
    //In this section we find D^2=LU
    //==========================================================================================

    
    //Allocation of memory for matrix L
    double** L;
    L = allocate_matrix(n-1, n-1);
    
    //Allocation of memory for matrix U
    double** U;
    U = allocate_matrix(n-1, n-1);
    
    //Allocation of memory for the permutation vector
    int* pi;
    pi = new int [n-1];
    
    PLUDecomposition(n-1, D2, L, U, pi);
    
    PrintMatrix(n-1, n-1, L, "L");
    PrintMatrix(n-1, n-1, U, "U");
    PrintVector(n-1, pi, "pi");
    
    deallocate_matrix(n-1, D2);
    
    //==========================================================================================


    //Allocating the memory for the u vector.
    double* u_old;
    u_old = new double [n-1];
    //For loop populates intial u with zero entries
    for (int i = 0; i<n-1; i++)
    {
        u_old[i] = 0;
    }
    //PrintVector(n-1, u_old, "u_old");
    
    //Allocating the uP vector. This will store the analytical results
    double*B;
    B = new double [n-1];
    
    //==========================================================================================
    //Specifying values of variables that will be required to make to the while loop function
    int count;
    count = 0;
    
    //Allocating the e vector, this will store the errors.
    double* e;
    e = new double [n-1];
    
    int i_max;
    //==========================================================================================
   
    do
    {
        for (int i=0; i<n-1; i++)
        {
           B[i] = exp((u_old[i]));
        }
     
        PrintVector(n-1, B, "B");
        PrintVector(n-1, pi, "before");
        
        SolveLinearSystem(n-1, L, U, pi, B);
        
        PrintVector(n-1, u_old, "old u");
        PrintVector(n-1, B, "new u");

        count++;
        
        //=============================================================================
        //Infinity Norm Calculation
        //=============================================================================
        for (int i=0; i<n-1; i++)
        {
            e[i] = std::abs(B[i] - u_old[i]);
        }
        
        i_max = 0; //sets initial i_max value of 0;
        for (int i=0; i<n-1; i++)
        {
            if (e[i]>e[i_max]) //compares value of each element of ek with the current max element in ek.
            {
                i_max = i;  //if ek[i] is greater than ek[i_max] then sets i_max = i.
            }
        }
        //==============================================================================
        
        for (int i=0; i<n-1; i++)
        {
            u_old[i]=B[i];
        }
        
        //u_old = copyVector(B,n);
        
        std::cout << "Iteration " << count << " has an Error = " << e[i_max] << std::endl; //outputs the value of Count and the error ..
        std::cout << std::endl;
        
    } while  (e[i_max]>10e-8 && count<100);
    
    
    //==========================================================================================

    //PrintVector(n+1, uPrimePrime, "uPrime");
  
    //PrintVector(count, e, "Errors");
    
    //==========================================================================================
    //Delete pointers to remove from the memory.
    
    delete u_old;
    delete e;
    delete B;
    
    //deallocate_matrix(n-1, D2);
    
    return 0;   //Program has been executed successfully.
}

double* copyVector(double* a_vector, int n)
{
    double* copy = new double[n];
    
    for (int i=0; i<n; i++)
    {
    copy[i] = a_vector[i];
    }
    
    return copy;
}


