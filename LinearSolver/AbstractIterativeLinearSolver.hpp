#ifndef ABSTRACTITERATIVELINEARSOLVERHEADERDEF
#define ABSTRACTITERATIVELINEARSOLVERHEADERDEF

#include "Matrix.hpp"
#include "Vector.hpp"
#include "LinearSystem.hpp"

class AbstractIterativeLinearSolver
{

  public:

    // Pure virtual method for solving Ax = b
    virtual void Solve(Vector* px) = 0;

    // Printing infos when iterations begin
    virtual void PrintHeader(const std::string solverName) const;

    // Printing infos when iterations terminate
    virtual void PrintFooter(const int k, const bool converged) const;

    // Print infos about current iterate
    virtual void PrintIteration(const int k, const double residualNorm,
                                const bool initialise = false) const;

    // Save iteration to file
    virtual void SaveIteration(const int k, const Vector* p_solution,
                               const int labelWidth=5) const;


  protected:

    // Max number of iterations
    int mMaxIterations;

    // User-specified tolerance
    double mTolerance;

};

#endif
