#include <iostream>
#include <cmath>

double** allocateMatrixMemory(int n_rows, int n_cols){
	double** matrix;
	matrix = new double* [n_rows];
	for (int i=0; i<n_rows; i++){
		matrix[i] = new double [n_cols];
	}
	return matrix;
}

void freeMatrixMemory(int n_rows, double** matrix){
	for (int i=0; i<n_rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

bool isAlmostZero(double number){
	if (number < 0){ // I make cases for negative number because abs(number) rounds the number.
		return (number >= -1e-8);
	}else{
		return (number <= 1e-8);
	}
}

double dot(double *v1, double *v2, int size){
	double dot_prod = 0;
	for (int i=0; i<size; i++){
		dot_prod += v1[i] * v2[i];
	}
	return dot_prod;
}

double* matrixTimesVector(double **matrix, double *vector, int mat_rows, int mat_cols, int vec_rows){
	double* result;
	if (mat_cols != vec_rows){
		std::cout << "Can't multiply "<< mat_rows << "x" << mat_cols;
		std::cout << "matrix, with a "<< vec_rows << "x1 vector."<<std::endl;
		result = NULL;
	}else{
		result = new double[mat_rows];
		for (int i=0; i<mat_rows; i++){
			result[i] = dot(matrix[i],vector, mat_cols);
		}
	}
	return result;
}

void printMat(double **matrix, int n_rows, int n_cols){
	for (int row=0; row < n_rows; row++){
		std::cout << "|";
		for (int col=0; col<n_cols; col++){
			if (matrix[row][col]>=0 && matrix[row][col]<10) std::cout << " ";
			std::cout << matrix[row][col] << " ";
		}
		std::cout << "|" << std::endl;
	}
}

void printV(double *vector, int size){
	if(vector == NULL){
		std::cout << "NULL vector" << std::endl;
	}else{
		for (int i=0; i<size; i++){
			if (vector[i]>=0 && vector[i]<10) std::cout << "| ";
			else std::cout << "|";
			if (isAlmostZero(vector[i])) std::cout << 0 << "|" << std::endl;
			else std::cout << vector[i] << "|" << std::endl;
		}
	}
}

double l2Norm(double* a_vector, int size){
	double norm = 0.0;
    for (int i=0; i<size; i++){
        norm += pow(a_vector[i],2.0);
    }
    return sqrt(norm);
}

double infinityNorm(double* a_vector, int size){
	double max_entry = std::abs(a_vector[0]);
	for (int i=1; i<size; i++){
		double next_entry = std::abs(a_vector[i]);
		if(next_entry > max_entry){
			max_entry = next_entry;
		}
	}
	return max_entry;
}

double* substractV(double *v1, double *v2, int size){
	double* result;
	result = new double[size];
	for (int i=0; i<size; i++){
		result[i] = v1[i] - v2[i];
	}
	return result;
}

double* addV(double *v1, double *v2, int size){
	double* result;
	result = new double[size];
	for (int i=0; i<size; i++){
		result[i] = v1[i] + v2[i];
	}
	return result;
}

double** addMat(double **m1, double **m2, int size){
	double** result;
	result = new double* [size];
	for (int i=0; i<size; i++){
		result[i] = new double[size];
		result[i] = addV(m1[i], m2[i], size);
	}
	return result;
}

double** substractMat(double **m1, double **m2, int size){
	double** result;
	result = new double* [size];
	for (int i=0; i<size; i++){
		result[i] = new double[size];
		result[i] = substractV(m1[i], m2[i], size);
	}
	return result;
}

double* vectorTimesConstant(double* vector, double constant, int size){
	double* result;
	result = new double[size];
	for (int i=0; i<size; i++){
		result[i] = vector[i]*constant;
	}
	return result;
}

double** matrixTimesConstant(double** matrix, double constant, int size){
	double** result;
	result = new double* [size];
	for (int i=0; i<size; i++){
		result[i] = new double[size];
		result[i] = vectorTimesConstant(matrix[i], constant, size);
	}
	return result;
}

double* getColumn(double** matrix, int index, int size){
	double* column = NULL;
	if (index >= size){
		std::cout<<"Error: Index out of range for getColumn @ " << index <<std::endl;	
	} else {
		column = new double [size];
		for (int row=0; row<size; row++){
			column[row] = matrix[row][index];
		}
	}
	return column;
}

double* getRow(double** matrix, int index, int size){
	double* row = NULL;
	if (index >= size){
		std::cout<<"Error: Index out of range for getRow @ " << index <<std::endl;	
	} else {
		row = new double [size];
		row = matrix[index];
	}
	return row;
}

double** matrixTimesMatrix(double** m1, double** m2, int size){
	double** result;
	result = allocateMatrixMemory(size, size);
	for (int r=0; r<size; r++){
		double *row = getRow(m1, r, size);
		for (int c=0; c<size; c++){
			double *col = getColumn(m2, c, size);
			result[r][c] = dot(row,col, size);
		}
	}
	return result;
}


bool isVectorAlmostZero(double* vector, int size){
	
    bool value = true;
	
    for (int i=0; i<size; i++){
		
        double entry = vector[i];
		
        /* If any of its entries is not a computer zero,
         return false i.e. not a zeros vector.*/
		if(!isAlmostZero(entry)) return false; 
	}
    
	return value; // After iterating through all entries, all of them are computer zeros.
}