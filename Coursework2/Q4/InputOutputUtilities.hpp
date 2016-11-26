
// Prints on screen an array v of doubles of lengthn .
// The vector name is also displayed
void PrintVector(int n, double* v, std::string vectorName);

// Prints on screen an array v of integers, of length n.
// The vector name is also displayed
void PrintVector(int n, int* v, std::string vectorName);

// Prints on screen an n-by-m array A of doubles, formatted as a matrix.
// The matrix name is also displayed
void PrintMatrix(int n, int m, double** A, std::string matrixName);

// Prints two columns of formatted output to visualise current iterations and errors
// A header can optionally be printed.
void PrintError(int n, double error, bool writeHeader = false);

// Saves an array of length n to a file
void SaveVectorToFile(int n, double* v, std::string fileName);

// Saves the errors vector in two columns, the first column is the 
// numbering from 0 to n.
void SaveErrorsVectorToFile(int n, double* v, std::string fileName);

