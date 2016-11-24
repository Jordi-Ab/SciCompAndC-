#include <cmath>
#include <iostream>
#include <stdexcept>
#include "matrix_allocation.hpp"
#include "LinearAlgebraLibrary.hpp"
#include "InputOutputUtilities.hpp"
#include "VecsAndMats.cpp"

/*----------Main Functions to perform PLU factorization.-----------*/

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
void PLUDecomposition (int n , double ** A , 
						double ** L , double ** U , 
						int * pi ){
	_initP(pi, n);
	copyMat(A, U, n, n);
	matrixToIdentity(L, n, n);
	//PrintMatrix(n, n, U, "Initial A: ");
	for(int row_at=0; row_at<n; row_at++){
		//print("row_at = ", false);
		//print(row_at);

		// Permutation step:
        int pivot_index = _findPivot(U, row_at, n);
        //print("pivot index: ", false);
        //print(pivot_index);
        if (row_at != pivot_index){
			//print("swap_rows: ");
			//PrintVector(2, pi, "pi");
			swapRows(row_at, pivot_index, U);
			//PrintMatrix(n, n, U, "Permuted A: ");
			swapElements(row_at, pivot_index, pi);
			//PrintVector(n, pi, "perm vec:");
		}
		
		toLprime(L, row_at, pivot_index);
		//PrintMatrix(n, n, L, "L': ");
        
        eliminationStep(U, L, row_at, n, n);
        //PrintMatrix(n, n, U, "Eliminated A: ");
        
	}

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

/*Main Functions to Solve a Linear System.*/
void SolveLinearSystem(int n, double** L, double** U,
						int* pi, double* b){

}


void BackSubstitution(int n ,double** U ,double* b){
	for(int i=n-1; i>=0; i--){
		
        double rhs = b[i]; // rhs stands for right hand side.
		
        for(int j=n-1; j>i; j--){
			rhs -= b[j]*U[i][j];
		}
		
        b[i] = rhs/U[i][i];
	}

}

void ForwardSubstitution ( int n , double ** L , double * b ){
	for(int i=0; i<n; i++){
        double rhs = b[i]; // rhs stands for right hand side.
		
        for(int j=0; j<i; j++){
			rhs -= (L[i][j]*b[j]);
		}
        b[i] = rhs/L[i][i];
	}

}




/*-------Some helpers to achive the PLU factorization.--------*/

void swapMatrixEntries(double** a_matrix, int row1, int col1, int row2, int col2){
	double temp = a_matrix[row1][col1];
	a_matrix[row1][col1] = a_matrix[row2][col2];
	a_matrix[row2][col2] = temp;
}

void swapElements(int ix1, int ix2, double* vector){
    double temp = vector[ix1];
    vector[ix1] = vector[ix2];
    vector[ix2] = temp;
}

void swapElements(int ix1, int ix2, int* vector){
    int temp = vector[ix1];
    vector[ix1] = vector[ix2];
    vector[ix2] = temp;
}

void swapRows(int ix1, int ix2, double** a_matrix){
    double* temp = a_matrix[ix1];
    a_matrix[ix1] = a_matrix[ix2];
    a_matrix[ix2] = temp;
}

/*
Returns a "n_rows"x"n_cols"
identity matrix.
*/
double** eyeMat(int n_rows, int n_cols){
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
        std::cout << "for eyeV."<<std::endl;
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

void matrixToIdentity(double** M, int n_rows, int n_cols){
	for(int r=0; r<n_rows; r++){
		for(int c=0; c<n_rows; c++){
			if (r == c) M[r][c] = 1;
			else M[r][c] = 0;
		}
	}
}

void copyMat(double** M1, double** M2, 
			int n_rows, int n_cols){
	for(int r=0; r<n_rows; r++){
		for(int c=0; c<n_rows; c++){
			M2[r][c] = M1[r][c];
		}
	}
}

double* copyVector(double* a_vector, int n){
	double* copy = new double[n];
	for (int i=0; i<n; i++){
		copy[i] = a_vector[i];
	}
	return copy;
}

int* permutationVector(int row1, int row2, int size){
    int* v = new int[size];
    if(row1>size || row2>size){
        std::cout << "Index out of bounds ";
        std::cout << "for permutationVector."<<std::endl;
        return NULL;
    }else{
        for(int i=0; i<size; i++){
            if(i == row1) v[i] = row2;
            else if(i == row2) v[i] = row1;
            else v[i] = i;
        }
    }
    return v;
}

void PermuteVector(int n, int* pi, double* v){
	double* temp = copyVector(v, n);
    for (int i=0; i<n; i++){
        int index = pi[i];
        if(index != i) v[i] = temp[index];
    } 
    delete[] temp;
}

void PermuteMatrix(int n, int* pi, double** M){
    double** temp = allocateMatrixMemory(n,n); /*
    temporary matrix.*/
    copyMat(M, temp, n, n);/*
    Copy the contents of M into temp.*/
    for (int r=0; r<n; r++){
        int index = pi[r];
        if(index != r) M[r] = temp[index];
    } 
    delete[] temp;
}

double** fullPermutationMatrix(int* pi, int size){
    double** perm_mat = allocateMatrixMemory(size,size);
    for (int r=0; r<size; r++){
    	int index_of_row = pi[r];
        double* row = eyeV(index_of_row, size);
        perm_mat[r] = row;
    }
    return perm_mat;
}

/*-------Private Methods not intended for use outside this script.---------*/
double* _eliminate(double *row1, double *row2, double factor, int vecs_size){
	
    double* result;
	result = new double[vecs_size];
	
    for (int i=0; i<vecs_size; i++){
		result[i] = row1[i] - factor*row2[i];
    }
    
	return result;
}

void _initP(int* P, int size){
	for(int i=0; i<size; i++){
		P[i] = i;
	}
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


