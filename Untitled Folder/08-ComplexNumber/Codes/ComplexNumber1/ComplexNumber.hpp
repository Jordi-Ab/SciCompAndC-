#ifndef COMPLEXNUMBERHEADERDEF
#define COMPLEXNUMBERHEADERDEF

#include <iostream>
class ComplexNumber
{
  public:

    // Overridden default constructor
    ComplexNumber(); 

    // Overridden insertion operator
    friend std::ostream& operator<<(
	                 std::ostream& output, 
	                 const ComplexNumber& z);

  private:

    // Real and imaginary parts
    double mRealPart;
    double mImaginaryPart;

};

#endif
