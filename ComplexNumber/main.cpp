#include <iostream>
#include <complexnumber.hpp>

int main(){
    // Printing a Complex Number
    ComplexNumber z1 = ComplexNumber(-1,2);
    std::cout << "Printing the complex number z1 = ";
    std::cout << z1 << std::endl;

    // Modulus, Argument and Power.
    ComplexNumber z(1.4,2.2);
    std::cout << "z = " << z << std::endl;
    std::cout << "|z| = ";
    std::cout << z.CalculateModulus() << std::endl;
    std::cout << "arg(z) = ";
    std::cout << z.CalculateArgument() << std::endl;
    std::cout << "z^4 = ";
    std::cout << z.CalculatePower(4) << std::endl;

    // Equality Operator
    ComplexNumber a(1.4,2.2);
    ComplexNumber b;

    b = a;

    std::cout << "b =" << b << std::endl;
}
