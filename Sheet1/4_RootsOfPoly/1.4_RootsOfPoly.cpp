/*
* This program finds roots of the quadratic equation *
*
* a(x^2) + bx + c = 0
*
* If a is 0 or if the equation has no real roots, the program exits with an error.
*/

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

/* Private function prototypes */
void GetCoefficients(double & a, double & b, double & c);
void SolveQuadratic(double a, double b, double c, double & x1, double & x2);
void DisplayRoots(double x1, double x2);
double getInput(std::string message);

/* Main program */
int main() {
   double a, b, c, r1, r2;

   GetCoefficients(a, b, c);

   try{
       SolveQuadratic(a, b, c, r1, r2);
       DisplayRoots(r1, r2);
   }catch (const std::invalid_argument& problem){
       std::cout << problem.what() << std::endl; // Prints out the error message.
   }
   return 0;
}

/*
 * Function: GetCoefficients
 * Usage: GetCoefficients(a, b, c);
 * --------------------------------
 * This function is responsible for reading in the coefficients
 * of a quadratic equation.  The values of the coefficients are
 * passed back to the main program in the variables a, b, and c,
 * which are reference parameters.
 */
void GetCoefficients(double & a, double & b, double & c) {
   std::cout << "Enter coefficients for the quadratic equation:" << std::endl;
   a = getInput("a: ") ;
   b = getInput("b: ") ;
   c = getInput("c: ") ;
}

/*
 * Function: SolveQuadratic
 * Usage: SolveQuadratic(a, b, c, x1, x2);
 * --------------------------------
 * This function finds the roots of the polynomial whose values are a, b and c.
 * Receives the roots x1 and x2 by reference and overwrites its values once the operations are done.
 * Returns an error when its roots are complex.
 */
void SolveQuadratic(double a, double b, double c, double & x1, double & x2){
    if (a==0) throw std::invalid_argument( "This is not a quadratic equation, coefficient \"a\" must be non-zero." );
    double discriminant = pow(b, 2.0) - 4.0*a*c;
    if (discriminant < 0){
        throw std::invalid_argument( "Complex Roots" );
    }else if(discriminant == 0){ // Case of a single root.
        x1 = (-b) / (2.0*a);
        x2 = 0;
    }else{
        x1 = (-b + sqrt(discriminant)) / (2.0*a);
        x2 = (-b - sqrt(discriminant)) / (2.0*a);
    }
}

// Prints the resulting roots on the console screen.
void DisplayRoots(double x1, double x2){
    if (x2 == 0){
        std::cout << "x = " << x1 << std::endl; // Case of a single root.
    }else{
        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;
    }
}

/*
 * Function: getInput
 * Usage: double x = getInput(prompt);
 * ----------------------------------
 * Asks the user for an input, if the input is not a number it
 * keeps asking until the user enters a number.
 *
 * The given "message" string is printed before reading the value.
 */
double getInput(std::string message){
    double input;
    while (true){
        std::cout << message;
        std::cin >> input;
        if(!std::cin.fail()) break;
        std::cout << "This is not a number, try again." << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
    return input;
}

