#include "myRandom.hpp"

static void initRandomSeed() {
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(NULL)));
        initialized = true;
    }
}

int randomInteger(int low, int high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (double(high) - low + 1);
    return int(floor(low + s));
}

double randomReal(double low, double high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (high - low);
    return low + s;
}

double** createRandomMatrix(int n_rows, int n_cols, bool integer){
	double** rand_matrix = _allocateMatrixMemory(n_rows,n_cols);
	for (int i=0; i<n_rows; i++){
		for (int j=0; j<n_cols; j++){
			if(integer){ // Matrix with random integer entries
				int entry = randomInteger(-9, 9);
				rand_matrix[i][j] = (double)entry;
			} else { // Matrix with random double precision entries
				double entry = randomReal(-9.9, 9.9);
				rand_matrix[i][j] = entry;
			}
		}
	}
	return rand_matrix;
}

double* createRandomVector(int size, bool integer){
	double* rand_vec;
	rand_vec = new double[size];
	for (int i=0; i<size; i++){
		if (integer){ // For random vectors of integers
			int entry = randomInteger(-9, 9);
			rand_vec[i] = (double)entry;
		}else{ // For random vectors of double precision
			double entry = randomReal(-9.9, 9.9); 
			rand_vec[i] = entry; 
		}
	}
	return rand_vec;
}



int myRandomInteger(){
    
    initRandomSeed();
    int r = rand();
    std::string str = std::to_string(r);
    char last_value = str[str.length()-1];
    int l = last_value - 48;
    
    if (l <= 1) l+=2;
    
    return l;
}

//*----------Internal Methods--------*//

double** _allocateMatrixMemory(int n_rows, int n_cols){
	double** matrix;
	matrix = new double* [n_rows];
	for (int i=0; i<n_rows; i++){
		matrix[i] = new double [n_cols];
	}
	return matrix;
}

void _freeMatrixMemory(int n_rows, double** matrix){
	for (int i=0; i<n_rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
