#include <iostream>
#include "InputOutputUtilities.cpp"
#include "LinearAlgebraLibrary.cpp"
#include "myRandom.cpp"

int main(){
    /*
    Things to modify: 
    Make PermuteVector work with the original permutation vector.
    */
    int n = myRandomInteger();

    int r1 = randomInteger(0, n-1);
    int r2 = randomInteger(0, n-1);

    int* pi = P(r1,r2, n);
    int* perm_vec = permutationVector(pi, n);
    printVector(n, perm_vec, "Permutation");

    //double** perm_mat = fullPermutationMatrix(pi, n);
    //PrintMatrix(n,n,perm_mat,"Permutation");

    double* a_vector = createRandomVector(n);
    printVector(n, a_vector, "Original");

    PermuteVector(n, perm_vec, a_vector);
    printVector(n, a_vector, "Permuted");

    delete[] pi;
    delete[] perm_vec;
    //freeMatrixMemory(n, perm_mat);

    return 0;
}


