#include <iostream>
#include "matrix_allocation.cpp"

/*Function: copyVector
---------------------------------------------
Returns a new vector that will hold the same
values and size as the given vector.
*/
double* copyVector(double* a_vector, int n){
	double* copy = new double[n];
	for (int i=0; i<n; i++){
		copy[i] = a_vector[i];
	}
	return copy;
}

/*
Function: swapElements
---------------------------------------------
Swaps the element at index "ix1", with the element
at index "ix2" inside a vector of doubles.

# Mutates the given vector.
*/
void swapElements(int ix1, int ix2, double* vector){
    double temp = vector[ix1];
    vector[ix1] = vector[ix2];
    vector[ix2] = temp;
}



/*Function: PermuteVector
---------------------------------------------
Given a permutation vector "pi", swaps entries inside
the given vector, corresponding to the entries of pi.

i.e. pi = [2,1,0,3,4] will swap entry 0 with entry 2
inside v.
*/
void PermuteVector(int n, int* pi, double* v){
	double* temp = copyVector(v, n);
    for (int i=0; i<n; i++){
        int index = pi[i];
        if(index != i) v[i] = temp[index];
    } 
    delete[] temp;
}

/*Function: permutationVector
---------------------------------------------
Returns a permutation vector that contains information
about the rows to be swapped inside a matrix, or the
entries to be swapped inside a vector.
# Vector respresentation of a permutation matrix.
*/
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

/*
Function: eyeV
---------------------------------------------
Returns a new pointer to a vector, having
zeros and a one in the given entry.

i.e. A unit vector like [0,1,0,......0]
*/
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
double** fullPermutationMatrix(int* pi, int size){
    double** perm_mat = allocateMatrixMemory(size,size);
    for (int r=0; r<size; r++){
    	int index_of_row = pi[r];
        double* row = eyeV(index_of_row, size);
        perm_mat[r] = row;
    }
    return perm_mat;
}

