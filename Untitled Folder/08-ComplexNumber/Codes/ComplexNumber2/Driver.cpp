#include <iostream>
#include "ComplexNumber.hpp"

int main(int argc, char* argv[])
{

  // Instantiate complex numbers
  ComplexNumber z(1.4,2.2);
  std::cout << "z = " << z << std::endl;
  std::cout << "|z| = " 
            << z.CalculateModulus() 
	    << std::endl
            << "arg(z) = " 
            << z.CalculateArgument() 
	    << std::endl
            << "z^4 = " 
            << z.CalculatePower(4) 
	    << std::endl;

}
