#include <string>
#include <stdlib.h>
#include <cmath>

static void initRandomSeed();

int randomInteger(int low, int high);

double randomReal(double low, double high);

double** createRandomMatrix(int n_rows, int n_cols, bool integer=true);

double* createRandomVector(int size, bool integer=true);

/*
 I created this function because the conventional way of
 creating random Integers, which is in the randomInteger
 function, is biased towards the lowest value of the range.
 When you run the program, the first generated number is
 almost always the lowest value on the range. 
 In this program the first time I called randomInteger 
 was to decide the size of the system to be solved, so almost
 always it returned a 2x2 system.
 So I hacked a function that the first time you run it returns
 a truly random Integer between 2 and 9.
 
 #Its not the most efficient way of creating a non biased 
 random Integer between an interval, but does the job 
 for this excercise.
*/
int myRandomInteger();


/*
Function: _allocateMatrixMemory
Usage: double** a_matrix = allocateMatrixMemory(2, 3)
---------------------------------------------
Saves space in the computer's memory to hold a
matrix of n_rows by n_cols size.
*/
double** _allocateMatrixMemory(int n_rows, int n_cols);

/*
Function: freeMatrixMemory
Usage: freeMatrixMemory(2, a_matrix)
--------------------------------------------------
Receives the number of rows of the matrix, and the
matrix itself for which you want to free the memory space. 
Deallocates the memory used by the given matrix.
*/
void _freeMatrixMemory(int n_rows, double** matrix);