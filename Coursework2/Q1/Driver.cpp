#include <iostream>
#include "InputOutputUtilities.cpp"
#include "LinearAlgebraLibrary.cpp"
#include "myRandom.cpp"


void testWithRandoms();/*
For testing the code with random 
row swaps of random vectors.*/

int main(){
    int n=3;

    int pi[3] = {1,2,0} ;
    PrintVector(n, pi, "P");

    double** perm_mat = fullPermutationMatrix(pi, n);
    PrintMatrix(n,n,perm_mat,"P");
    freeMatrixMemory(n, perm_mat);

    double a_vector[3] = {8,3,1};
    PrintVector(n, a_vector, "v");

    PermuteVector(n, pi, a_vector);
    PrintVector(n, a_vector, "P*v");

	//testWithRandoms();
    return 0;
}

void testWithRandoms(){

	std::cout << "Testing with random permutations";
	std::cout << " and vectors." << std::endl;
	std::cout << " " << std::endl;

	int n = myRandomInteger();
	std::cout << " Random size: " << n << std::endl;
	bool print_permutation_matrix = false;

	int r1 = randomInteger(0, n-1);
    int r2 = randomInteger(0, n-1);
    std::cout << " Swap row "<< r1;
    std::cout <<" with row "<< r2 << std::endl;
    std::cout << " " << std::endl;

    int* pi = permutationVector(r1,r2, n);
    //int perm_vec[6] = {2,0,1,3,4,5};
    PrintVector(n, pi, "Random P");

	if (print_permutation_matrix){
		double** perm_mat = fullPermutationMatrix(pi, n);
    	PrintMatrix(n,n,perm_mat,"Random P");
    	freeMatrixMemory(n, perm_mat);
	}
    
    double* a_vector = createRandomVector(n);
    PrintVector(n, a_vector, "Random v");

    PermuteVector(n, pi, a_vector);
    PrintVector(n, a_vector, "Permuted v");

    delete[] pi;
    delete[] a_vector;

}


