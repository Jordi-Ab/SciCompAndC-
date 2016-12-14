#include <assert.h>
#include "LinearSystem.hpp"

// Specialised constructor
LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
{
  // Size of the problem. Check if A and b have compatible sizes
  mSize = A.GetNumberOfRows();
  assert(A.GetNumberOfColumns() == mSize);
  assert(b.GetSize() == mSize);

  // Local copies of A and b
  mpA = new Matrix(A);
  mpb = new Vector(b);
}

// Copy constructor
LinearSystem::LinearSystem(const LinearSystem& otherLinearSystem)
{
  // Copying private members from otherLinearSystem
  mpA = new Matrix( *(otherLinearSystem.GetMatrix()) );
  mpb = new Vector( *(otherLinearSystem.GetRightHandSide()) );
  mSize = (otherLinearSystem.GetRightHandSide())->GetSize() ;
}

// Destructor
LinearSystem::~LinearSystem()
{
  // Cleaning
  delete mpA;
  delete mpb;
}

// Gives access to A
Matrix* LinearSystem::GetMatrix() const
{
  return mpA;
}

// Gives access to b
Vector* LinearSystem::GetRightHandSide() const
{
  return mpb;
}

// Computes residual
void LinearSystem::CalculateResidual(const Vector* x, Vector* residual) const
{
  *residual = (*mpA) * (*x) - (*mpb);
}
