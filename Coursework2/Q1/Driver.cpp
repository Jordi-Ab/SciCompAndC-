#include <iostream>
#include "InputOutputUtilities.cpp"
#include "LinearAlgebraLibrary.cpp"
#include "myRandom.cpp"

void q1_b();

int main(){
    int n = myRandomInteger();

    int r1 = randomInteger(0, n-1);
    int r2 = randomInteger(0, n-1);

    int* pi = P(r1,r2, n);
    double* perm_vec = permutationVector(pi, n);
    printVector(n, perm_vec, "Permutation");

    double** perm_mat = fullPermutationMatrix(pi, n);
    PrintMatrix(n,n,perm_mat,"Permutation");

    double* a_vector = createRandomVector(n);
    printVector(n, a_vector, "Original");

    permuteVector(pi, a_vector, n);
    printVector(n, a_vector, "Permuted");

    delete[] pi;
    delete[] perm_vec;
    freeMatrixMemory(n, perm_mat);

    return 0;
}

void q1_b(){

}

