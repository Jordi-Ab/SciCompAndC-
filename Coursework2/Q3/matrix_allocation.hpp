
/*
Function: allocateMatrixMemory
Usage: double** a_matrix = allocateMatrixMemory(2, 3)
---------------------------------------------
Saves space in the computer's memory to hold a
matrix of n_rows by n_cols size.
*/
double** allocateMatrixMemory(int n_rows, int n_cols);

/*
Function: freeMatrixMemory
Usage: freeMatrixMemory(2, a_matrix)
--------------------------------------------------
Receives the number of rows of the matrix, and the
matrix itself for which you want to free the memory space. 
Deallocates the memory used by the given matrix.
*/
void freeMatrixMemory(int n_rows, double** matrix);