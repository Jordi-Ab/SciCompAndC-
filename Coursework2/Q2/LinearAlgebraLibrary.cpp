#include <cmath>
#include <stdexcept>
#include "matrix_allocation.hpp"
#include "LinearAlgebraLibrary.hpp"
#include "InputOutputUtilities.hpp"

/*----------Main Functions to perform PLU factorization.-----------*/
void PLUDecomposition(double** A, double** L, double** U, int* P, int n){
		/*
		Receives a square matrix,
		Overwrites .... 
		of the matrix, in the form PA = LU,
		such that A = P^T.L.U
		P -> Permutation matrix
		L -> Inverse of the Elimination matrix
		U -> Upper triangular form of the matrix 
		*/

		//toUpperTriangular(U, P, L, n,n);
		/*When taking a matrix to Upper Triangular with
		partial pivoting, the stored matrices are as follows
		Mn.Pn....M2.P2.M1.P1.A = U. So that, A = LU,
		With L = (Mn.Pn....M2.P2.M1.P1)^-1. However, 
		in that way L is not Lower triangular, so we have to
		manipulate L so that the factorization ends up as
		PA = LU, with L being lower triangular.
		toLprime(L,n) function does this. */
}

void toUpperTriangular(double** matrix, double* perm_vec,
						double** L, 
						int n_rows, int n_cols){
	PrintMatrix(n_rows, n_cols, matrix, "Initial A: ");
	for(int row_at=0; row_at<n_rows; row_at++){
		print("row_at = ", false);
		print(row_at);
		// Permutation step:
        int pivot_index = _findPivot(matrix, row_at, n_rows);
        print("pivot index: ", false);
        print(pivot_index);
        if (row_at != pivot_index){
			int *pi = _P(row_at, pivot_index, n_rows);
			print("swap_rows: ");
			PrintVector(2, pi, "pi");
			permuteMatrix(pi, matrix, n_rows);
			PrintMatrix(n_rows, n_cols, matrix, "Permuted A: ");
			permuteVector(pi, perm_vec, n_rows);
			PrintVector(n_rows, perm_vec, "perm vec:");
		}
		
		toLprime(L, row_at, pivot_index);
		PrintMatrix(n_rows, n_cols, L, "L': ");
        
        eliminationStep(matrix, L, row_at, n_rows, n_cols);
        PrintMatrix(n_rows, n_cols, matrix, "Eliminated A: ");
        
	}
}

void permutationStep(double** matrix, int current_row, 
					int pivot_index, int n_rows){
	 
}

void eliminationStep(double** matrix, double** L, 
						int position, int n_rows, int n_cols){
	
    double* pivot_row = matrix[position];
	double pivot_entry = pivot_row[position];
	
    for (int row=position+1; row<n_rows; row++){
		
        double* next_row = matrix[row];
		double first_element = next_row[position];
		
        if (!isAlmostZero(first_element)){ 
        /* If the element is zero, or almost zero, 
        there's no need to eliminate the row.*/
			
            double factor = first_element/pivot_entry;
            // Factor used to eliminate the row underneath.

            L[row][position] = factor;
			/* Store factor in the elimination matrix.
			Actually, its already the inverse of the 
			elimination matrix*/

			double* new_row = _eliminate(next_row, pivot_row, factor, n_cols);
			/* I create a new_row with the result of the eliminations step, 
			so I can test if the elimination step results in a row 
			of zeros before overwriting the content of the row.*/
			
            if (isVectorAlmostZero(new_row, n_rows)){ 
            	/* New row results in a row of zeros.
				(Implies linearly dependant row in the matrix).*/
                throw std::runtime_error("System is either not invertible, or has infinte solutions.");
            }
            
			matrix[row] = new_row;
			// Overwite the current row with the result of the elimination step.
			
		}
	}
}

void toLprime(double** L, int row_at, int pivot_index){
	for (int entry = 0; entry <= row_at-1; entry++){
		int row1 = row_at;      int col1 = entry;
		int row2 = pivot_index; int col2 = entry;
		swapMatrixEntries(L, row1, col1, row2, col2);
	}
} 


/*-------Some helpers to achive the PLU factorization.--------*/

void swapMatrixEntries(double** a_matrix, int row1, int col1, int row2, int col2){
	double temp = a_matrix[row1][col1];
	a_matrix[row1][col1] = a_matrix[row2][col2];
	a_matrix[row2][col2] = temp;
}

double** eyeMat(int n_rows, int n_cols){
	/*
	Returns a "n_rows"x"n_cols"
	identity matrix.
	*/
	double** identity = allocateMatrixMemory(n_rows, n_cols);
	for(int r=0; r<n_rows; r++){
		for(int c=0; c<n_rows; c++){
			if(r==c) identity[r][c] = 1;
			else identity[r][c] = 0;
		}
	}
	return identity;
}

double* eyeV(int entry, int size){
    double* vector = new double[size];
    if (entry>size){
        std::cout << "Index out of bounds ";
        std::cout << "for identityV."<<std::endl;
        delete[] vector;
        return NULL;
    }else{
        for (int i=0; i<size; i++){
           if (i == entry) vector[i] = 1;
           else vector[i] = 0;
        }
    }
    return vector;
}

double** copyMat(double** matrix, int n_rows, int n_cols){
	/*
	Returns a copy of the given "n_rows"x"n_cols"
	"matrix"
	*/
	double** copy = allocateMatrixMemory(n_rows, n_cols);
	for(int r=0; r<n_rows; r++){
		for(int c=0; c<n_rows; c++){
			copy[r][c] = matrix[r][c];
		}
	}
	return copy;
}

double* permutationVector(int* pi, int size){
    double* v = new double[size];
    int entry1 = pi[0];
    int entry2 = pi[1];
    if(entry1>size || entry2>size){
        std::cout << "Index out of bounds ";
        std::cout << "for permutationVector."<<std::endl;
        return NULL;
    }else{
        for(int i=0; i<size; i++){
            if(i == entry1) v[i] = entry2;
            else if(i == entry2) v[i] = entry1;
            else v[i] = i;
        }
    }
    return v;
}

void permuteVector(int* pi, double* v, int size){
    int entry1 = pi[0];
    int entry2 = pi[1];
    if(entry1>size || entry2>size){
        std::cout << "Index out of bounds ";
        std::cout << "for permuteVector."<<std::endl;
    }else{
        double temp = v[entry1];
        v[entry1] = v[entry2];
        v[entry2] = temp;
    }
}

void permuteMatrix(int* pi, double** a_matrix, int size){
    int row1_index = pi[0];
    int row2_index = pi[1];
    if(row1_index>size || row2_index>size){
        std::cout << "Index out of bounds ";
        std::cout << "for permuteMatrix."<<std::endl;
    }else{
        double* temp = a_matrix[row1_index];
		a_matrix[row1_index] = a_matrix[row2_index];
		a_matrix[row2_index] = temp;
		//delete[] temp;
    }
}

double** fullPermutationMatrix(int* pi, int size){
    double** perm_mat = allocateMatrixMemory(size,size);
    int entry1 = pi[0];
    int entry2 = pi[1];
    for (int row=0; row<size; row++){
        double* v;
        if(row == entry1) v = eyeV(entry2, size);
        else if(row == entry2) v = eyeV(entry1, size);
        else v = eyeV(row, size);
        perm_mat[row] = v;
    }
    return perm_mat;
}

bool isAlmostZero(double number, double error_tol){
	if (number < 0){ 
		/* I make cases for negative number because 
		abs(number) rounds the number.*/
		return (number >= -error_tol);
	}else{
		return (number <= error_tol);
	}
}

bool isVectorAlmostZero(double* vector, int size, double error_tol){
	
    bool value = true;
	
    for (int i=0; i<size; i++){
		
        double entry = vector[i];
		
        /* If any of its entries is not a computer zero,
         return false i.e. not a zeros vector.*/
		if(!isAlmostZero(entry, error_tol)) return false; 
	}
    
	return value; 
	/* After iterating through all entries, 
	all of them are computer zeros.*/
}

/*-------Private Methods not intended for use outside this script.---------*/
int* _P(int ix1, int ix2, int size){
    // Contains information about the rows to be swapped
    // inside a vector.
    if(ix1>size || ix2>size){
        std::cout << "Index out of bounds ";
        std::cout << "for pi."<<std::endl;
        return NULL;
    }else{
        int* result = new int[2];
        result[0] = ix1;
        result[1] = ix2;
        return result;
    }
}

double* _eliminate(double *row1, double *row2, double factor, int vecs_size){
	
    double* result;
	result = new double[vecs_size];
	
    for (int i=0; i<vecs_size; i++){
		result[i] = row1[i] - factor*row2[i];
    }
    
	return result;
}

double* _initP(int size){
	double* P0 = new double[size];
	for(int i=0; i<size; i++){
		P0[i] = i;
	}
	return P0;
}

int _findPivot(double** matrix, int position, int size){
	
    double pivot = std::abs(matrix[position][position]);
	int pivot_index = position;
	
    for (int row=position+1; row<size; row++){
		
        double possible_pivot = std::abs(matrix[row][position]);
		
        if (possible_pivot > pivot){
				pivot = possible_pivot;
				pivot_index = row;
		}
	}
	
    return pivot_index;
}


