//==========================================================================================
//Gareth Calvert - 4265464 - University of Nottingham - 2016/2017
//==========================================================================================
#include <cmath>
#include <iostream>

//void PrintVector(int n, double* v, std::string vectorName); //Required only if doing a Test Print.

void ChebyshevDifferentiationMatrix(int n, double* x, double** D)
{
    ///////////////////////////////////////////////////////////////////////
    //This section computes x values.
    //Defining pi myself due to email.
    double* mPi;
    mPi = new double;
    *mPi = 4.0*atan(1.0);
    
    //Calculating and storing the set of n+1 Gauss-Chebyshev-Lobatto points
    for (int j = 0; j<=n; j++)
    {
        x[j] = cos((*mPi*j)/n);
    }
    
    delete mPi; //Delete mPi as no longer needed
    
    //PrintVector(n+1, x, "x"); //Test Print
    
    ///////////////////////////////////////////////////////////////////////
    //This section creates and fills in the c vector.
    //Allocation of memory for c array.
    double* c;
    c = new double [n+1];
    
    //For loop, is used to fill in the elements of c.
    for (int i=0; i<n+1; i++)
    {
        if (i==0 || i==n) //c_0 = 2 and c_n = 2
        {
            c[i] = 2;
        }
        else    //The rest of the values of c are 1.
        {
            c[i] = 1;
        }
    }
    
    //PrintVector(n+1, c, "c"); //Test Print
    
    ///////////////////////////////////////////////////////////////////////
    //For loop to populate the entries of the D matrix
    for (int i = 0; i<n+1; i++)
    {
        for (int j = 0; j<n+1; j++)
        {
            if (i==0 && j==0)   //D_00 has a specific entry
            {
                D[i][j] = (2*pow(n,2)+1)/6;
            }
            
            else if (i==n && j==n)  //D_nn has a specific entry
            {
                D[n][n] = - (2*pow(n,2)+1)/6;
            }
            
            else if (i==j && i!=0 && i!=n)    //Diagonal entries, except for 00 and nn.
            {
                D[j][j] = -x[j]/(2*(1-pow(x[j], 2)));
            }
            
            else if (i!=j)  //Everything else.
            {
                D[i][j] = (c[i]*pow(-1, (i+j)))/(c[j]*(x[i]-x[j]));
            }
            
            
        }
    }
    
    ///////////////////////////////////////////////////////////////////////
    
    delete c; // No longer required
    
    
} //Function end
