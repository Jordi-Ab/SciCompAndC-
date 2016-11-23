#include <iostream>
#include "matrix_allocation.cpp"

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
void permuteVector(int n, int* pi, double* v){
    int entry1 = pi[0];
    int entry2 = pi[1];
    if(entry1>n || entry2>n){
        std::cout << "Index out of bounds ";
        std::cout << "for permuteVector."<<std::endl;
    }else{
        double temp = v[entry1];
        v[entry1] = v[entry2];
        v[entry2] = temp;
    }
}

void swapElements(int ix1, int ix2, double* vector){
    double temp = vector[ix1];
    vector[ix1] = vector[ix2];
    vector[ix2] = temp;
}

void PermuteVector(int n, int* pi, double* v){
    for (int i=0; i<n; i++){
        int index = pi[i];
        if(index > i) swapElements(index, i, v);
    } 
}

int* P(int ix1, int ix2, int size){
    // Contains information about the rows to be swapped
    // in a vector.
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

int* permutationVector(int* pi, int size){
    int* v = new int[size];
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

double* identityV(int entry, int size){
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

double** fullPermutationMatrix(int* pi, int size){
    double** perm_mat = allocateMatrixMemory(size,size);
    int entry1 = pi[0];
    int entry2 = pi[1];
    for (int row=0; row<size; row++){
        double* v;
        if(row == entry1) v = identityV(entry2, size);
        else if(row == entry2) v = identityV(entry1, size);
        else v = identityV(row, size);
        perm_mat[row] = v;
    }
    return perm_mat;
}

