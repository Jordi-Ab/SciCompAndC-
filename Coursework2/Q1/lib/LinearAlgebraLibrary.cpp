#include <iostream>
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
void permuteVector(int* pi, double* v){
    int entry1 = pi[0];
    int entry2 = pi[1];
    double temp = v[entry1];
    v[entry1] = v[entry2];
    v[entry2] = temp;
}

int* permutationVector(int ix1, int ix2){
    // Contains information about the rows to be swapped
    // in a vector.
    int* result = new int[2];
    result[0] = ix1;
    result[1] = ix2;
    return result;
}

double* identityV(int entry, int size){
    double* vector = new double[size];
    for (int i=0; i<size; i++){
       if (i == entry) vector[i] = 1;
       else vector[i] = 0;
    }
    return vector;
}

double** fullPermutationMatrix(int* pi, int size){
    double** perm_mat = allocateMatrixMemory(size,size);
    int entry1 = pi[0];
    int entry2 = pi[1];
    for (int row=0; row<size; row++){
        double* v;
        if(row == entry1) v = identityV(entry1, size);
        else if(row == entry2) v = identityV(entry2, size);
        else v = identityV(row, size);
        perm_mat[row] = v;
    }
    return perm_mat;
}

