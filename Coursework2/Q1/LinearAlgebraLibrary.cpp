#include <iostream>
#include "matrix_allocation.cpp"

/*
Function: copyVector
Usage: copyVector(vector, 4);
---------------------------------------
Returns a new vector which is the copy of the
given vector.
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
Usage: swapElements(0, 2, a_vector);
---------------------------------------
Swaps the element located at index "ix1"
with the element located at index "ix2"
inside a given vector.

# Mutates the given vector.
*/
void swapElements(int ix1, int ix2, double* vector){
    double temp = vector[ix1];
    vector[ix1] = vector[ix2];
    vector[ix2] = temp;
}


/*
 Function: permuteVector
 Usage: permuteVector(3, perm_vec, a_vec)
 ---------------------------------------
 Receives:
    . "n" -> Size of the vector and the
       permutation vector (must be equally sized)
    ."pi" -> A Permutation vector.
        (Contains information about the rows to be permuted)
    . "v" -> The vector to be permuted.
 Returns:
    . Nothing, overwrites the given vector "v".

 Has the effect of swaping the rows of "v" according to
 the given permutation vector "pi".
*/
void PermuteVector(int n, int* pi, double* v){
	double* temp = copyVector(v, n);
    for (int i=0; i<n; i++){
        int index = pi[i];
        if(index != i) v[i] = temp[index];
    } 
    delete[] temp;
}

/*
 Function: permutationVector
 Usage: permutationVector(3, 0, 4);
 ---------------------------------------
 Given row1, row2, and the size of the vector.
 Returns a permutation vector that has information
 about the rows to be permuted on a matrix,
 (or the entries to be permuted in a vector).
 In other words, contains the indices where the
 entries of a vector should be located.

 i.e. 
 permutationVector(3, 0, 4) = [3,1,2,0,4]
 That means a swap of element in 0 with element in 3

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
Usage: eyeV(2, 5);
---------------------------------------
Returns a vector of zeros of given size, 
with a 1 located at the given "entry".
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

/*
Function: fullPermutationMatrix
Usage: fullPermutationMatrix(perm_vec, 10);
---------------------------------------
Given a permutation vector, returns its
corresponding permutation Matrix.
(Identity Matrix with rows swapped.)
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

