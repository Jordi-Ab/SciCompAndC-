#include "complexnumber.hpp"

//CONSTRUCTORS-DESTRUCTORS:

ComplexNumber::ComplexNumber(){
    m_re = 0.0;
    m_im = 0.0;
}

ComplexNumber::ComplexNumber(const double re, const double im){
    m_re = re;
    m_im = im;
}


//PUBLIC FUNCTIONS:

double ComplexNumber::CalculateModulus() const{
    return sqrt(std::pow(m_re,2) + std::pow(m_im,2));
}

double ComplexNumber::CalculateArgument() const{
    return atan2(m_im, m_re);
}

ComplexNumber ComplexNumber::CalculatePower(const double n) const{

    // Retrieve modulus and arguments
    double modulus = CalculateModulus();
    double argument = CalculateArgument();

    // Modulus and argument of z^n (using de Moivre's formula)
    modulus = std::pow(modulus,n);
    argument *= n;

    // Return the new complex numbers
    return ComplexNumber(modulus* cos(argument),
                        modulus* sin(argument));

}


//PRIVATE FUNCTIONS


//OVERWRITTEN OPERATORS:

std::ostream& operator<<(std::ostream& output,
                         const ComplexNumber& z){
    // Pretty formatting
    output << "(" << std::setprecision(5) << z.m_re << " ";

    if (z.m_im >= 0){
        output << "+ " << z.m_im << "i";
    }else{
        output << "- " << -z.m_im << "i";
    }

    output << ")";

    return output;
}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber& z){
    m_re = z.m_re;
    m_im = z.m_im;
    return *this;
}

ComplexNumber& ComplexNumber::operator-() const{
    m_re = -z.m_re;
    m_im = -z.m_im;
    return *this;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber& z) const{

}

ComplexNumber ComplexNumber::operator-(const ComplexNumber& z) const{

}

