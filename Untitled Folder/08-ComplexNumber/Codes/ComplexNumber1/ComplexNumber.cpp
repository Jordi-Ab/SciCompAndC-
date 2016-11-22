#include "ComplexNumber.hpp"

// Overridden default constructor
ComplexNumber::ComplexNumber()
{
  mRealPart = 0.0;
  mImaginaryPart = 0.0;
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
