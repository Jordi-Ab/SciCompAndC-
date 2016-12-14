#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP


#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystem
{

  public:

    // Specialised Constructor
    LinearSystem(const Matrix& A, const Vector& b);

    // Copy Constructor
    LinearSystem(const LinearSystem& otherLinearSystem);

    // Destructor
    ~LinearSystem();

    // Accessor for A and b
    Matrix* GetMatrix() const;
    Vector* GetRightHandSide() const;

    // Residual calculation
    void CalculateResidual(const Vector* x, Vector* r) const;

  private:

    // Hiding default constructor
    LinearSystem();

    // Matrix A
    Matrix* mpA;

    // Right hand side b
    Vector* mpb;

    // Problem size
    int mSize;

};

#endif // LINEARSYSTEM_HPP
