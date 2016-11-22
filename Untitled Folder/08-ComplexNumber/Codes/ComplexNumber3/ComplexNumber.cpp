#include <iostream>
#include <cmath>
#include "ComplexNumber.hpp"

// Public methods -----------------------------------
// Overridden default constructor
ComplexNumber::ComplexNumber()
{
  mRealPart = 0.0;
  mImaginaryPart = 0.0;
}

// Specialised constructor
ComplexNumber::ComplexNumber(const double x, const double y)
{
  mRealPart = x;
  mImaginaryPart = y;
}

double ComplexNumber::CalculateModulus() const
{
  return sqrt(pow(mRealPart,2) + pow(mImaginaryPart,2));
}

double ComplexNumber::CalculateArgument() const
{
  return atan2(mImaginaryPart, mRealPart);
}

ComplexNumber ComplexNumber::CalculatePower(const double n) const
{

  // Retrieve modulus and arguments
  double modulus = CalculateModulus();
  double argument = CalculateArgument();

  // Modulus and argument of z^n (using de Moivre's formula)
  modulus = pow(modulus,n);
  argument *= n;

  // Return the new complex numbers
  return ComplexNumber( modulus * cos(argument),
                        modulus * sin(argument) );

}

ComplexNumber& ComplexNumber::
                   operator=(const ComplexNumber& z)
{
  mRealPart = z.mRealPart;
  mImaginaryPart = z.mImaginaryPart;
  return *this;
}

// Overridden insertion operator
std::ostream& operator<<(std::ostream& output,
                         const ComplexNumber& z)
{
  // Pretty formatting 
  output << "(" << z.mRealPart << " ";
  if (z.mRealPart >= 0)
  {
    output << "+" << z.mImaginaryPart << "i";
  }
  else
  {
    output << "-" << -z.mImaginaryPart << "i";
  }
  output << ")";

  return output;
}
