#ifndef CONVERGENCECRITERIONHEADERDEF
#define CONVERGENCECRITERIONHEADERDEF

class ConvergenceCriterion
{

  public:

    // Specialised Constructor
    ConvergenceCriterion(const double tolerance);

    // Method for checking convergence based on the residual norm
    // True if || residual || < tolerance
    bool TestConvergence(double residualNorm) const;

  private:

    // Hidden default constructor
    ConvergenceCriterion();

    // Tolerance
    double mTolerance;

};

#endif

