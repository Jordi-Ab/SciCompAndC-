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
    b=-a;
    std::cout << "-b =" << b << std::endl;


    ComplexNumber first(1.1, 2.2);
    ComplexNumber second(1.1, 2.2);

    std::cout << "c =" << first << std::endl;
    std::cout << "d =" << second << std::endl;

    // Plus Operator
    std::cout << "c + d =" << first+second << std::endl;

    // Substract Operator
    std::cout << "c - d =" << first-second << std::endl;

    std::cout << "Re(c) = "<< first.getReal() << std::endl;
    std::cout << "Im(c) = " << first.getImaginary() << std::endl;

    // Comparative statements.
    if(first == second) std::cout << "c=d" << std::endl;
    if(first != second) std::cout << "c!=d" << std::endl;

}
