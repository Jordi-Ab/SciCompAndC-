#include <stdexcept>
#include <string>
// Compile dependencies just once in the Driver.
#include "Chebyshev.cpp"
#include "VecsAndMats.cpp"
#include "InputOutputUtilities.cpp"
#include "LinearAlgebraLibrary.cpp"

const double TOL = 1e-8;
const int MAX_ITER = 100;

void f(double* xs, int n);
/*
Things missing:

Comments on the .hpp's
Add a readme.txt to explain the extra files.
Make all dependency files equal.
Clean code:
	free all memory.
	place comments.
	put functions on the right places.
	delete unused functions.
*/
int main(){
	int n = 40;
	double* mesh = new double[n];
	double** D = allocateMatrixMemory(n,n);

	ChebyshevDifferentiationMatrix(n-1, mesh, D);

	double** K = matrixTimesMatrix(D, D, n);/*
	The second order differential matrix is
	defined as D dot D.  */
	freeMatrixMemory(n, D); // D no longer needed.

	double* row_1 = eyeV(0, n); // unit vector [1,0,0,...,0]
	double* row_n = eyeV(n-1, n); // unit vector [0,0,...,1]

	K[0] = row_1;
	K[n-1] = row_n;/*
	Place unit vectors on  the first and last rows of the
	Differential matrix for the Boundary Conditions.*/

	int* pi = new int[n];
	double** L = allocateMatrixMemory(n, n);
	double** U = allocateMatrixMemory(n, n);

	PLUDecomposition(n, K, L, U, pi);

	freeMatrixMemory(n, K); // K no longer needed.

	double* prev_u = new double[n]; // Solution of previous iter.
	zerosV(prev_u, n);

	double* next_u = new double[n]; // Will hold the solution.
	copyV(next_u, prev_u, n);

	double* errors = new double[MAX_ITER];
	
	int iter = 1;
	while(true){
		
		f(next_u,n); // Evaluate the rhs function at next_u.
		next_u[0] = 0; // Left Boundary Condition
		next_u[n-1] = 0; // Right Boundary Condition

		SolveLinearSystem(n, L, U, pi, next_u);

		double* difference = substractV(next_u, prev_u, n);
		double norm_of_error = infinityNorm(difference,n);
		errors[iter-1] = norm_of_error;
		delete[] difference;

		if (iter > MAX_ITER){ /*
		Failed to converge*/
			std::cout << "Failed to converge";
			std::cout << "for iteration" << iter;
			throw std::runtime_error("Iterations exceeded"); /* 
			Stop the program.*/
		} else if (norm_of_error<=TOL){/*
		Found a solution*/
			std::cout << "Done" << std::endl;
			PrintVector(n, next_u, "Result");
			break; // Exit while loop.
		}else{ /* 
		keep iterating */
			iter++;
			copyV(prev_u, next_u, n); /*
			store the content of next_u on prev_u
			and keep iterating.*/
			PrintVector(n, next_u, "u");
		}
	}

	/*------Writing results on Files-------*/
	bool use_complete_path = true;
	std::string cwd = "";
	if(use_complete_path){
		cwd = "/Users/user/Documents/Maestria/SciCompCpp/SciCompCpp_git/Coursework2/Q4/";
	}/*
	On my computer, c++ doesn't save the files
	in the current working directory, so I have
	to provide the full path of the working dir.*/
	
	SaveVectorToFile(n, mesh, cwd+"grid.dat");
	SaveVectorToFile(n, next_u, cwd+"solution.dat");
	SaveErrorsVectorToFile(iter, errors, cwd+"error.dat");

	delete[] mesh;
	delete[] next_u;
	delete[] prev_u;
	delete[] pi;
	delete[] errors;
	freeMatrixMemory(n, L);
	freeMatrixMemory(n, U);

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



