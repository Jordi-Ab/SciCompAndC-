#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <iostream>
#include <iomanip>
#include <cmath>
class ComplexNumber{

public:

    //CONSTRUCTORS-DESTRUCTORS:

    /*
    Constructor(Default): ComplexNumber
    -----------------------------------
    */
    ComplexNumber();

    /*
    Constructor(Default): ComplexNumber
    -----------------------------------
    */
    ComplexNumber(const double re, const double im);

    //PUBLIC FUNCTIONS:

    /*
    Function: CalculateModulus
    -----------------------------------
    */
    double CalculateModulus() const;

    /*
    Function: CalculateArgument
    -----------------------------------
    */
    double CalculateArgument() const;

    /*
    Function: CalculatePower
    -----------------------------------
    */
    ComplexNumber CalculatePower(const double n) const;

    //OVERWRITTEN OPERATORS:

    /*
    Operator: <<
    -----------------------------------
    */
    friend std::ostream& operator<<(std::ostream& output, const ComplexNumber& z);

    /*
    Operator: =
    -----------------------------------
    */
    ComplexNumber& operator=(const ComplexNumber& z);

    /*
    Operator: -
    -----------------------------------
    */
    ComplexNumber operator-() const;
    ComplexNumber operator-(const ComplexNumber& z) const;

    /*
    Operator: +
    -----------------------------------
    */
    ComplexNumber operator+(const ComplexNumber& z) const;

private:

    //INSTANCE VARIABLES
    double m_re;
    double m_im;

    //PRIVATE FUNCTIONS

};

#endif // COMPLEXNUMBER_H
