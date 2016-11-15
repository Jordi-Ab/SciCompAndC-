#include <iostream>
#import "InputOutputUtilities.cpp"
//#include "LinearAlgebraLibrary.cpp"

//void printVector(int n, int* v, std::string vectorName = "");
int* permutationVector(int ix1, int ix2, int size);

int main(){
    int* perm_vec = permutationVector(2,3,4);
    printVector(4, perm_vec);
    return 0;
}


