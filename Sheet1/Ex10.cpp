/*
This script performs the following vector and matrix operations:

u - v, Au, Au - v, 4A - 3B, AB. Where:

   |1|      |6|      |1 5 0|      |-2 0 1|
u =|2|, v = |5|, A = |7 1 2|, B = | 1 0 0|
   |3|      |4|      |0 0 1|      | 4 1 0|

* The best way to do this would be to create a class that can perform
any operation between vectors and matrices. But I think we'll get there
later on.
*/

#include <iostream>
#include <cassert>

static const int ARRAY_SIZE = 3;

int dot(int v1[], int v2[]);
int plus(int v1[], int v2[]);

int main(){
	int u[ARRAY_SIZE] = {1,2,3};
	int v[ARRAY_SIZE] = {6,5,4};
	int A[ARRAY_SIZE][ARRAY_SIZE] = {{1,5,0},{7,1,2},{0,0,1}};
	int B[ARRAY_SIZE][ARRAY_SIZE] = {{-2,0,1},{1,0,0},{4,1,0}};
	
	int u_dot_v = dot(u,v);
	std::cout << u_dot_v << std::endl;
	return 0;
}

int dot(int v1[], int v2[]){
	int dot_prod = 0;

	for (int i=0; i<ARRAY_SIZE; i++){
		dot_prod += v1[i] * v2[i];
	}

	return dot_prod;
}

int dot(int v1[], int v2[]){
	int dot_prod = 0;

	for (int i=0; i<ARRAY_SIZE; i++){
		dot_prod += v1[i] * v2[i];
	}

	return dot_prod;
}



