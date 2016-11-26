//==========================================================================================
//Gareth Calvert - 4265464 - University of Nottingham - 2016/2017
//==========================================================================================
#include <iostream>
#include<cmath>
//==========================================================================================
//Function interfaces of functions declared in this cpp file.
//==========================================================================================
//void PermuteVector(int n, int* pi, double* v);
//==========================================================================================
//Functions are used in debugging phase, when doing test print outs
//==========================================================================================
void PrintMatrix(int n, int m, double** A, std::string matrixName);
void PrintVector(int n, double* v, std::string vectorName);
void PrintVector(int n, int* v, std::string vectorName);
//==========================================================================================
//Functions stored in another cpp, used for matrix allocation
//==========================================================================================
double **allocate_matrix(int n, int m);
void deallocate_matrix(int n, double **A);


//==========================================================================================
//==========================================================================================
void PermuteVector(int n, int* pi, double* v)
{
    int *temp, *element ; //Create Pointers, needed as temporary values
    temp = new int[n];
    element = new int;
    
    //Loop extracts the "order" from the permutation vector and maps the result.
    for (int i = 0; i<n; i++)
    {
        *element = double(pi[i]);
        temp[i] = v[*element-1];
    }
    
    delete element; //Delete as no longer needed.
    
    //Overwrite vector v with the temporary vector.
    for (int i = 0; i<n; i++)
    {
        v[i]=temp[i];
    }
    
    
    //Delete temp as no longer need
    delete temp;
}

//===============================================================================================

void PLUDecomposition(int n, double** A, double** L, double** U, int* pi)
{
    //This function follows the Pseudocode 1 in the Coursework Sheet
    //====================================================================================
    
    //Setting L equal to the identity
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (i==j)
            {
                L[i][j] = 1;
            }
            else
            {
                L[i][j] = 0;
            }
        }
    }
    
    
    //PrintMatrix(n, n, L, "Initial L"); //Test Print to ensure L was being created correctly
    
    //Setting U equal to A
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            U[i][j] = A[i][j];
        }
    }
    
    //PrintMatrix(n, n, U, "Intial U"); //Test Print to ensure U was being created correctly
    
    
    
    //Setting permutation vector equal to the identity i.e. 1,2,3,....
    for (int i=0; i<n; i++)
    {
        pi[i] = i+1;
    }
    
    //PrintVector(n, pi, "Permutation"); Test Print
    
    //==========================================================================================
    //Creation of pointer values to have for the operation of the proceeding loops.
    //==========================================================================================
    
    //used in the testing for the largest U_l,k value
    double* biggest;
    biggest = new double;
    //m will be used as the value of the row which contains the max(U_l,k)
    int* m;
    m = new int;
    //temp is a vector that is used as a temp storage device when swapping rows or elements
    double* temp;
    temp = new double;
    
    //==========================================================================================
    
    for (int k = 0; k<=n-2; k++)
    {
        *biggest = std::abs(U[k][k]);   //initial value for testing for max
        *m = k;                 //initial row number of max value
        
        for (int l=k; l<=n-1; l++ )
        {
            if(*biggest<std::abs(U[l][k]))    //if bigger than the current, change biggest and m to new values
            {
                *biggest = std::abs(U[l][k]);
                *m = l;
            }
        }
        
        if (*m!=k)    //if m is not equal to k, do the following
        {
            for (int j = 0; j<n; j++) //For loop used to swap rows k and m in U
            {
                *temp = U[k][j];
                U[k][j] = U[*m][j];
                U[*m][j] = *temp;
            }
            
            //Swap rows and k and m in Permutation
            *temp = pi[k];
            pi[k] = pi[*m];
            pi[*m] = *temp;
            
            
            if (k>=1)
            {
                for (int j=0; j<=k-1; j++)
                {
                    *temp = L[k][j];
                    L[k][j]=L[*m][j];
                    L[*m][j] =*temp;
                    
                }
            }
        }
        
        for (int j= k+1; j<=n-1; j++)
        {
            L[j][k] = U[j][k]/U[k][k];
            
            for (int i=0; i<n; i++)
            {
                U[j][i] = U[j][i] - L[j][k]*U[k][i];
                
            }
            
        }
        
    }
    
}   //Function end


//==========================================================================================
//==========================================================================================

void BackSubstitution(int n, double** U, double* b)
{
    double* x;
    x = new double [n];
    
    //Calculating the value of b_n, index is different in array due element numeration.
    x[n-1]=b[n-1]/U[n-1][n-1];
    
    //Sum is used temporarily to work out each iteration of the backward substitution.
    double *sum;
    sum = new double;
    
    //For loop used, to follow the formula used for back substitution
    //formula appears in the Coursework Background PDF.
    for(int i=n-2; i>=0; i--)
    {
        *sum = 0;   //Needs set to zero for every iteration before being used in the next for loop.
        
        //This for loop is used to compute the sum, which is required for the formula to calculate the b_i.
        for(int j=i+1; j<=n-1; j++)
        {
            *sum +=  U[i][j]*x[j];
        }
        
        x[i]=(b[i]-*sum)/U[i][i];    //This formula computes the next b_i solution
    }
    
    //No longer needed so remove sum from memory.
    delete sum;
    
    for (int i = 0; i<n; i++)
    {
        b[i] = x[i];
    }
    
    delete x;
    
    //No need to return b as it is a pointer.
}

//==========================================================================================
//==========================================================================================


void ForwardSubstitution(int n, double** L, double* b)
{
    double* y;
    y = new double[n];
    
    y[0]=b[0]/L[0][0];
    
    double* sum;
    sum = new double;
    
    for (int i = 1; i<n; i++)
    {
        *sum = 0;
        for (int j = 0; j<i; j++)
        {
            *sum += L[i][j]*y[j];
        }
        
        y[i] = (b[i]-*sum)/L[i][i];
    }
    
    //Copying the y vector into the b vector.
    for (int i = 0; i<n; i++)
    {
        b[i] = y[i];
    }
    
    delete y;   //Delete y as results are now stored in b.
    
}

//==========================================================================================
//==========================================================================================


void SolveLinearSystem(int n, double** L, double** U, int* pi, double* b)
{
    
    
    PermuteVector(n, pi, b); //Apply permutation vector pi to b to get Pb
    //PrintVector(n, b, "Getting Pb"); //Test print when debugging
    
    ForwardSubstitution(n, L, b); //Find y s.t. Ly = Pb
    //PrintVector(n, b, "After forwards"); //Test print when debugging
    
    BackSubstitution(n, U, b);  //Find x s.t. Ux = y
    //PrintVector(n, b, "After backwards"); //Test print when debugging
    
}

//==========================================================================================
//==========================================================================================


