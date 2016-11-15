#import <iostream>
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
//void permuteVector(int n, int* pi, double* v){

//}

int* permutationVector(int ix1, int ix2, int size){
    int* result = new int[size];
    if (ix1 >= size || ix2 >= size){
        std::cout << "Index out of bounds for Permutation Vector" << std::endl;
        result = NULL;
    }else{
        for (int i=0; i<size; i++){
            if (ix1 == i) result[i] = ix2;
            else if (ix2 == i) result[i] = ix1;
            else result[i] = i;
        }
    }

    return result;
}
