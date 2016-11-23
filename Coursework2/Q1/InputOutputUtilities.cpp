#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <assert.h>

// Prints on screen an array v of doubles of lengthn .
// The vector name is also displayed
void PrintVector(int n, double* v, std::string vectorName = ""){
  std::cout << "Vector " << vectorName << ": "<< std::endl;
  if(v == NULL) std::cout << "NULL vector" << std::endl;
  else{
      for (int i=0; i<n; i++){
        std::cout << vectorName << "[" << i << "] = " << v[i] << std::endl;
      }
      std::cout << std::endl;
  }
}

// Prints on screen an array v of integers, of length n.
// The vector name is also displayed
void PrintVector(int n, int* v, std::string vectorName = ""){
    std::cout << "Vector " << vectorName << ": "<< std::endl;
    if(v == NULL) std::cout << "NULL vector" << std::endl;
    else{
        for (int i=0; i<n; i++){
          std::cout << vectorName << "[" << i << "] = " << v[i] << std::endl;
        }
        std::cout << std::endl;
    }
}

// Prints on screen an n-by-m array A of doubles, formatted as a matrix.
// The matrix name is also displayed
void PrintMatrix(int n, int m, double** A, std::string matrixName)
{
  std::cout << "Matrix " << matrixName << std::endl;
  for (int i=0; i<n; i++)
    {
      for (int j=0; j<m; j++)
      {
	std::cout << std::setw(14)
	          << std::setprecision(5)
	          << std::scientific 
	          << A[i][j];
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
}


// Prints two columns of formatted output to visualise current iterations and errors
// A header can optionally be printed.
void PrintError(int n, double error, bool writeHeader = false)
{
  if (writeHeader)
  {
    std::cout << std::setw(14) << "n"
	      << std::setw(14) << "error" << std::endl;
  }
  std::cout << std::setw(14) 
            << std::setprecision(5) 
            << n
            << std::setw(14) 
            << std::setprecision(5) 
            << error 
	    << std::endl; 
}

// Saves an array of length n to a file
void SaveVectorToFile(int n, double* v, std::string fileName)
{

  // Format output
  std::ofstream output_file;
  output_file.setf(std::ios::scientific,std::ios::floatfield);
  output_file.precision(6);

  // Open file (and perform a check)
  output_file.open(fileName);
  assert(output_file.is_open());

  // Write data
  for (int i=0; i<n; i++)
  {
    output_file << std::setw(15) << v[i] << std::endl;
  }

  // Close file
  output_file.close();

}
