#include <iostream>
#include <cassert>
#include "JacobiSolver.hpp"

// Specialised constructor
JacobiSolver::
JacobiSolver( 
    const LinearSystem* pLinearSystem, 
    const Vector* pInitialGuess, 
    const int maxIterations, 
    const double tolerance,
    const bool saveData)
{

  // Initialising protected variables
  // inherited from AbstractIterativeLinearSolver
  mMaxIterations = maxIterations;
  mTolerance = tolerance;

  // Initialising private variables 
  mpInitialGuess = pInitialGuess;
  mpLinearSystem = pLinearSystem;
  mpConvergenceCriterion = new ConvergenceCriterion(mTolerance);
  mSaveData = saveData;

}

// Destructor
JacobiSolver::~JacobiSolver()
{
  delete mpConvergenceCriterion;
}

// Solution method
void JacobiSolver::Solve(Vector* px)
{

  // Check size
  assert( px->GetSize() == mpInitialGuess->GetSize() );

  // Print header (inherited protected method from abstract class)
  PrintHeader("Jacobi method");

  // Assign variables to improve readability
  Matrix rA = *(mpLinearSystem->GetMatrix());
  Vector rb = *(mpLinearSystem->GetRightHandSide());
  int size = rA.GetNumberOfRows();

  // Temporary vector
  Vector y(size);

  // Iterator
  int k = 0;

  // Initialise solution to initial guess
  (*px) = (*mpInitialGuess);

  // Compute residual
  Vector* p_residual = new Vector( mpLinearSystem->GetRightHandSide()->GetSize() );
  mpLinearSystem->CalculateResidual(px,p_residual);

  // Residual norm
  double residual_norm;
  residual_norm = p_residual->CalculateNorm(2);

  // Print and eventually save first iteration
  PrintIteration(k,residual_norm,true);
  if (mSaveData)
  {
    SaveIteration(k,px);
  }

  // Convergence test
  bool converged = mpConvergenceCriterion->TestConvergence(residual_norm);

  // Start iterations
  while ( (k < mMaxIterations) && !converged )
  {

    for (int i=1; i<=size; i++)
    {
       y(i) = 0.0;
       for (int j=1; j<=size; j++)
       {
	 if (i!=j)
	 {
	   y(i) += rA(i,j) * (*px)(j);
	 }

       }
       y(i) = ( rb(i) - y(i) )/rA(i,i);
    }

    // Update solution
    *px = y;
    k++;

    // Update residual and residual norm
    mpLinearSystem->CalculateResidual(px,p_residual);
    residual_norm = p_residual->CalculateNorm(2);

    // Check convergence
    converged = mpConvergenceCriterion->TestConvergence(residual_norm);

    // Print and eventually save current iteration
    PrintIteration(k,residual_norm);
    if (mSaveData)
    {
      SaveIteration(k,px);
    }

  }

  // Print final message
  PrintFooter(k,converged);

  // Clean
  delete p_residual;

}
