#include <iostream>
#include "ComplexNumber.hpp"

int main(int argc, char* argv[])
{

  // Instantiate complex numbers
  ComplexNumber u(1.4,2.2);

  // Test assignment operator
  ComplexNumber z;
  z = u;
  std::cout << "u = " << u << std::endl;
  std::cout << "z = " << z << std::endl;

  // Test unary - operator
  z = -u;
  std::cout << "z = -u =  " << z << std::endl;

  // Test binary + operator
  ComplexNumber w(2.1,3.3);
  z = u + w;
  std::cout << "w = " << w << std::endl;
  std::cout << "z = u + w = " << z << std::endl;

  // Test binary - operator
  z = u - w;
  std::cout << "z = u - w = " << z << std::endl;

}
