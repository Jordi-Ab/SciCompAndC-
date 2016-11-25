
/*-Main Functions to perform PLU factorization.-*/
void PLUDecomposition (int n , double ** A ,
                       double ** L , double ** U ,
                       int * pi);

void toUpperTriangular(double** matrix, int* perm_vec,
						double** L, 
						int n_rows, int n_cols);

void eliminationStep(double** matrix, double** L, 
					int position, int n_rows, int n_cols);

void toLprime(double** L, int row_at, int pivot_index);

void SolveLinearSystem(int n, double** L, double** U,
						int* pi, double* b);


void BackSubstitution(int n ,double** U ,double* b);

void ForwardSubstitution ( int n , double ** L , double * b );

/*-Some helpers to achive the PLU factorization.-*/

void swapMatrixEntries(double** a_matrix, int row1, 
	int col1, int row2, int col2);

void swapElements(int ix1, int ix2, double* vector);

void swapElements(int ix1, int ix2, int* vector);

void swapRows(int ix1, int ix2, double** a_matrix);

void matrixToIdentity(double** M, int n_rows, int n_cols);

double** eyeMat(int n_rows, int n_cols);

double* eyeV(int entry, int size);

//Copies the contents of M1 into M2.
void copyMat(double** M1, double** M2,
					int n_rows, int n_cols);


double* copyVector(double* a_vector, int n);

void copyV(double* v1, double* v2, int n);

int* permutationVector(int row1, int row2, int size);

void PermuteVector(int n, int* pi, double* v);

void PermuteMatrix(int n, int* pi, double** M);

double** fullPermutationMatrix(int* pi, int size);

/*-Private Methods not intended for use outside this script.-*/

double* _eliminate(double *row1, double *row2, 
					double factor, int vecs_size);

void _initP(int* pi, int size);

int _findPivot(double** matrix, int position, int size);


