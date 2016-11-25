#include "Chebyshev.cpp"
#include "VecsAndMats.cpp"
#include "InputOutputUtilities.cpp"
#include "matrix_allocation.cpp"
#include "LinearAlgebraLibrary.cpp"

void f(double* xs, int n);
double infinityNorm(double* a_vector, int size);

int main(){
	int n = 20;
	double* mesh = new double[n];
	double** D = allocateMatrixMemory(n,n);

	ChebyshevDifferentiationMatrix(n-1, mesh, D);
	PrintMatrix(n,n, D, "Diff");

	double** K = matrixTimesMatrix(D, D, n);
	freeMatrixMemory(n, D); // D no longer needed.
	PrintMatrix(n,n, K, "Diff^2");

	double* row_1 = eyeV(0, n);
	double* row_n = eyeV(n-1, n);

	K[0] = row_1;
	K[n-1] = row_n;/*
	Modify the first and last rows of the
	Differential matrix for the Boundary Conditions.*/

	PrintMatrix(n,n, K, "Diff^2");

	int* pi = new int[n];
	double** L = allocateMatrixMemory(n, n);
	double** U = allocateMatrixMemory(n, n);

	PLUDecomposition(n, K, L, U, pi);

	PrintMatrix(n,n, K, "K");
	PrintMatrix(n,n, L, "L");
	PrintMatrix(n,n, U, "U");
	PrintVector(n, pi, "P");

	//freeMatrixMemory(n, K); // K no longer needed.
	//delete[] row_1;
	//delete[] row_n;

	double* prev_u = new double[n]; // Will hold the solution.
	zerosV(prev_u, n);
	PrintVector(n, prev_u, "initial u:");
	double* next_u = new double[n];
	copyV(next_u, prev_u, n);
	
	while(true){
		f(next_u,n);
		next_u[0] = 0;
		next_u[n-1] = 0;

		SolveLinearSystem(n, L, U, pi, next_u);

		double* difference = substractV(next_u, prev_u, n);
		if (infinityNorm(difference,n) <= 1e-8){
			std::cout << "Done" << std::endl;
			PrintVector(n, next_u, "Result");
			break;
		}else{

			copyV(prev_u, next_u, n); /*
			store in prev_u the contents of next_u 
			and keep iterating.*/
		}
	}

	SaveVectorToFile(n, mesh, "grid.dat");
	SaveVectorToFile(n, next_u, "solution.dat");

	return 0;
}

double f(double x){
	return exp(x);
}
void f(double* xs, int n){
	for (int i=0; i<n; i++){
		xs[i] = f(xs[i]);
	}
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


