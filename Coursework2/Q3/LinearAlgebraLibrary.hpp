
/*
Function: PLUDecomposition
---------------------------------------------
Overwrites the contents of the given pi vector, 
L, and U matrices.

Performs a factorization of the matrix A of the
PA = LU form
such that A = P^T.L.U
pi -> vector representation of the permutation matrix P
L -> Inverse of the Elimination matrix (Lower triangular)
	(Modified in such a way that it is still lower triangular
	after performing partial permutations)
U -> Upper triangular form of the matrix \
*/
void PLUDecomposition (int n , double ** A ,
                       double ** L , double ** U ,
                       int * pi);

/*
Function: eliminationStep
---------------------------------------------
Performs an elimination step according to the given 
position, which is the pivot entry you are currently at.
i.e. Eliminates rows underneath the given position.
Stores the factors used to perform elimination in the
given L matrix.
*/
void eliminationStep(double** matrix, double** L, 
					int position, int n_rows, int n_cols);

/*
Function: toLprime
---------------------------------------------
where Lprime is equal to L, but with the 
subdiagonal entries permuted.

*When taking a matrix to Upper Triangular with
partial pivoting L stops being Lower triangular,
because of the permutaions.
Wo we have to manipulate L so that the factorization
ends up as PA = LU, with L being lower triangular.
toLprime(L,n) function does this. 
*/
void toLprime(double** L, int row_at, int pivot_index);

/*
Function: SolveLinearSystem
---------------------------------------------
Solves a Linear System of the form LU x = Pb, where
P L and U are the PLU decomposition of a matrix A.
*/
void SolveLinearSystem(int n, double** L, double** U,
						int* pi, double* b);

/*
Function: BackSubstitution
---------------------------------------------
Solves a Linear system by backward substitution.
Assumes the given matrix "U" is in Upper triangular
form.
*/
void BackSubstitution(int n ,double** U ,double* b);

/*
Function: ForwardSubstitution
---------------------------------------------
Solves a Linear system by forward substitution.
Assumes the given matrix "L" is in Lower triangular
form.
*/
void ForwardSubstitution ( int n , double ** L , double * b );

/*-Some helpers to achive the PLU factorization.-*/

/*
Function: swapMatrixEntries
---------------------------------------------
Swaps the element at row1, col1; with the element
at row2, col2 inside the given matrix.

Mutates the given matrix.
*/
void swapMatrixEntries(double** a_matrix, int row1, 
	int col1, int row2, int col2);

/*
Function: swapElements
---------------------------------------------
Swaps the element at index "ix1", with the element
at index "ix2" inside a vector of doubles.
*/
void swapElements(int ix1, int ix2, double* vector);
void swapElements(int ix1, int ix2, int* vector); /*
Its counterpart for a vector of ints.*/

/*
Function: swapRows
---------------------------------------------
Swaps the row at index "ix1", with the row
at index "ix2" inside a matrix.
*/
void swapRows(int ix1, int ix2, double** a_matrix);

/*
Function: matrixToIdentity
---------------------------------------------
Receives a pointer to a matrix, and fills it
with zeros and ones in the diagonal.
*/
void matrixToIdentity(double** M, int n_rows, int n_cols);

/*
Function: eyeMat
---------------------------------------------
Returns a new pointer to a matrix, having
zeros and ones in the diagonal.
*/
double** eyeMat(int n_rows, int n_cols);

/*
Function: eyeV
---------------------------------------------
Returns a new pointer to a vector, having
zeros and a one in the given entry.

i.e. A unit vector like [0,1,0,......0]
*/
double* eyeV(int entry, int size);

/*Function: copyMat
---------------------------------------------
Copies the contents of M2 into M1.
Overwrites M1 with the content of M2.
*/
void copyMat(double** M1, double** M2,
					int n_rows, int n_cols);

/*Function: copyVector
---------------------------------------------
Returns a new vector that will hold the same
values and size as the given vector.
*/
double* copyVector(double* a_vector, int n);

/*Function: copyV
---------------------------------------------
Copies the contents of v2 into v1.
Overwrites v1 with the content of v2.
*/
void copyV(double* v1, double* v2, int n);

/*Function: permutationVector
---------------------------------------------
Returns a permutation vector that contains information
about the rows to be swapped inside a matrix, or the
entries to be swapped inside a vector.
# Vector respresentation of a permutation matrix.
*/
int* permutationVector(int row1, int row2, int size);

/*Function: PermuteVector
---------------------------------------------
Given a permutation vector "pi", swaps entries inside
the given vector, corresponding to the entries of pi.

i.e. pi = [2,1,0,3,4] will swap entry 0 with entry 2
inside v.
*/
void PermuteVector(int n, int* pi, double* v);

/*Function: PermuteMatrix
---------------------------------------------
Given a permutation vector "pi", swaps rows inside
the given matrix, corresponding to the entries of pi.

# Equivalent to multiplying by a Permutation Matrix.

i.e. pi = [2,1,0,3,4] will swap row 0 with row 2
inside M.
*/
void PermuteMatrix(int n, int* pi, double** M);

/*Function: fullPermutationMatrix
---------------------------------------------
Given a permutation vector "pi", returns its 
corresponding Permutation Matrix.
i.e. pi = [2,1,0,3,4] will return:
|0 0 1 0|
|0 1 0 0|
|1 0 0 0|
|0 0 0 1|
*/
double** fullPermutationMatrix(int* pi, int size);

/*-Private Methods not intended for use outside this script.-*/

/*  _eliminate
Eliminates the first entry of row2 using the given 
factor and the given row1.
i.e. new_row = row2 - (factor * r1)
# Returns a new pointer.
*/
double* _eliminate(double *row1, double *row2, 
					double factor, int vecs_size);
/*  _initP
Receives an empty pointer and its size.
Initializes a permutation vector.
i.e. [0,1,2,3,....,size]
*/
void _initP(int* pi, int size);

/*  _findPivot
Finds the biggest entry in absolute value underneath
the given position. Returns the index where that entry
is located.
Ex:
int pivot = findPivot(matrix, 0, 4);

Matrix:
| 0  2 -1  6 |
| 1  0  2  1 |
|-1  0  3 -5 |
| 2  1  0  2 |
 
For column 0, pivot is located at row 4.
Hence, pivot = 4.

*/
int _findPivot(double** matrix, int position, int size);


