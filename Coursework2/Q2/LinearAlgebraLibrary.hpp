
/*-Main Functions to perform PLU factorization.-*/
void PLUDecomposition(double** A, double** L, 
						double** U, int* P, int n);

void toUpperTriangular(double** matrix, int* perm_vec,
						double** L, 
						int n_rows, int n_cols);

void permutationStep(double** matrix, int current_row, 
					int pivot_index, int n_rows);

void eliminationStep(double** matrix, double** L, 
					int position, int n_rows, int n_cols);

void toLprime(double** L, int row_at, int pivot_index);

/*-Some helpers to achive the PLU factorization.-*/

void swapMatrixEntries(double** a_matrix, int row1, 
	int col1, int row2, int col2);

double** eyeMat(int n_rows, int n_cols);

double* eyeV(int entry, int size);

double** copyMat(double** matrix, 
					int n_rows, int n_cols);

double* permutationVector(int* pi, int size);

void permuteVector(int* pi, double* v, int size);

void permuteMatrix(int* pi, double** a_matrix, int size);
void permuteMatrix(double* perm_vec, double** a_matrix, int size);

double** fullPermutationMatrix(double* perm_vec, int size);

bool isAlmostZero(double number, double error_tol=1e-10);

bool isVectorAlmostZero(double* vector, int size, 
						double error_tol=1e-10);

/*-Private Methods not intended for use outside this script.-*/
int* _P(int ix1, int ix2, int size);

double* _eliminate(double *row1, double *row2, 
					double factor, int vecs_size);

double* _initP(int size);

int _findPivot(double** matrix, int position, int size);


