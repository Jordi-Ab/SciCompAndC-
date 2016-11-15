#include <iostream>
#include "InputOutputUtilities.cpp"
#include "LinearAlgebraLibrary.cpp"
#include "matrix_allocation.cpp"


int main(){
    int* perm_vec = permutationVector(2,3);

    double a_vector[4] = {7,1,4,2};

    permuteVector(perm_vec, a_vector);
    printVector(4, a_vector, "Permuted Vector");

    double** perm_mat = fullPermutationMatrix(perm_vec, 4);
    PrintMatrix(4,4,perm_mat,"Permutation M");
    return 0;
}



