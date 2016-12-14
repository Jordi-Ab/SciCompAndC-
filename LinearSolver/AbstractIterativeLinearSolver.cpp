#include <cassert>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>


#include "AbstractIterativeLinearSolver.hpp"

// Printing infos when iterations begin
void AbstractIterativeLinearSolver::PrintHeader(const std::string solverName) const{
    std::cout << "------------------------------------------------"
        << std::endl;
    std::cout << " Attempt to solve Ax = b using " + solverName
        << std::endl;
    std::cout << " max number of iterations = " << mMaxIterations
        << std::endl;
    std::cout << " tolerance = " << mTolerance
        << std::endl;
    std::cout << "------------------------------------------------"
        << std::endl;
}

// Printing infos when iterations terminate
void AbstractIterativeLinearSolver::PrintFooter(const int k, const bool converged) const{
  
    if (converged){
        std::cout << "------------------------------------------------"
            << std::endl;
        std::cout << "Method converged after "  << k << " iterations"
            << std::endl;
    }else{
        std::cout << "------------------------------------------------"
            << std::endl;
        std::cout << "Method failed to converge after " << k << " iterations"
            << std::endl;
    }

}

// Printing infos about current iteration
void AbstractIterativeLinearSolver::PrintIteration(const int k,
                                                   const double residualNorm,
                                                   const bool initialise) const{

    // At the first iterate, print the table header
    if (initialise){
        std::cout << std::setw(10) << "Iteration"
                  << std::setw(25) << "error estimate"
                  << std::endl;
    }

    // Residual norm is printed with scientific notation
    std::cout << std::setw(10) << k
              << std::scientific
              << std::setprecision(6)
              << std::setw(25) << residualNorm
              << std::endl;

}

// Saving current iteration to file
void AbstractIterativeLinearSolver::
SaveIteration(const int k, const Vector* p_solution, const int labelWidth) const{

    // Setting strem file precision
    std::ofstream output_file;
    output_file.setf(std::ios::scientific,std::ios::floatfield);
    output_file.precision(6);

    // Opening file
    std::ostringstream iterate_label;
    iterate_label.width(labelWidth);
    iterate_label.fill('0');
    iterate_label << k;

    std::string file_name = "solution_" + iterate_label.str() + ".dat";

    output_file.open(file_name);
    assert(output_file.is_open());

    // Write data
    for (int i=0; i<p_solution->GetSize(); i++)
    {
    output_file << std::setw(15) << p_solution->Read(i) << std::endl;
    }

    // Close file
    output_file.close();

}
