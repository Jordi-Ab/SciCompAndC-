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

}
