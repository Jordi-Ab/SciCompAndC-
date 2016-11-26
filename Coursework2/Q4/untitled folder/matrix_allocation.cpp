//==========================================================================================
//Gareth Calvert - 4265464 - University of Nottingham - 2016/2017
//==========================================================================================

//This cpp file contains two functions.
//The function allocate_matrix dynamically allocates a pointer to be a matrix
//The function deallocate_matrix is used to delete the matrix from the memory

double **allocate_matrix(int n, int m)
{

    //The idea behind dynamically allocating a matrix is to first create a pointer which is an array.
    //Said array is then has another pointer array inserted into each element of the intial array.
    //The result being an array of arrays, which can be used as a matrix.

    double **A;
    A = new double* [n];

    for (int i=0; i<n; i++)
        {
            A[i] = new double [m];
        }

    return A;

}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void deallocate_matrix(int n, double **A)
{
    //The loop deletes the array as an element from the intial array.
    for (int i=0; i<n; i++)
        {
            delete [] A[i];
        }

    delete [] A;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
