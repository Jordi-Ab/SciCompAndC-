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

int main(){
	int u[3] = {1,2,3};
	int v[3] = {6,5,4};
	int A[3][3] = {{1,5,0},{7,1,2},{0,0,1}};
	int B[3][3] = {{-2,0,1},{1,0,0},{4,1,0}};

	int u_dot_v = dot(u,v);
	std::cout << u_dot_v << endl;
	return 0;
}

int dot(int v1[], int v2[]){
	int size1 = sizeof(v1)/sizeof(int);
	int size2 = sizeof(v2)/sizeof(int);
	assert(size1 == size2);

	int dot_prod = 0;
	for (int i=0; i<=size1; i++){
		dot_prod += v1[i] * v2[i];
	}
}

