#include <iostream>
#include <cmath>

// Function prototypes
void coordinatesFromExcercise(int counter, double & x, double & y, double & z);
void getCoordinates(double & x, double & y, double & z);
double getNumber(std::string message);
void printPolarCoordinates(double x, double y, double z);
double atan2(double y, double x);


// Main Program
int main(){
    double x;
    double y;
    double z;

    std::cout << " " << std::endl;
    std::cout << "This program transforms Cartesian Coordinates (x, y, z) to Polar Coordinates." << std::endl;

    /*
     * Define inputFromUser depending on whether you want to ask
     * the user for the coordinates or you want to compute the coordinates
     * given on the excercise sheet.
     * "inputFromUser = false" will compute the coordiantes of the excercise sheet.
     * "inputFromUser = true" will ask the user to enter the desired coordinates to be transformed.
     */
    bool inputFromUser = false;

    if(inputFromUser){
        getCoordinates(x,y,z);
        printPolarCoordinates(x, y, z);
    }else{
        for (int i=0; i<4; i++){
            coordinatesFromExcercise(i, x, y, z);
            printPolarCoordinates(x, y, z);
        }
    }
    return 0;
}

/*
 * Function: coordinatesFromExcercise(
 * Usage: coordinatesFromExcercise(i);
 * --------------------------------
 * Excercise 5 asks us to transform to Polar Coordinates some given Carteian Coordinates,
 * this function overwrites the values of x, y and z to be those given in the excercise sheet.
 */
void coordinatesFromExcercise(int counter, double & x, double & y, double & z) {
   switch (counter){
       case 0:
           x = 3.0;
           y = 4.5;
           z = -1.0;
           break;
       case 1:
           x = -5.2;
           y = 2.5;
           z = 1.4;
           break;
       case 2:
           x = -1.0;
           y = -1.0;
           z = 0.0;
           break;
       case 3:
           x = 0.0;
           y = 3.0;
           z = 3.0;
           break;
   }
}


/*
 * Function: GetCoordinates
 * Usage: GetCoordinates(x, y, z);
 * --------------------------------
 * This function is responsible for reading in the
 * Cartesian Coordinates to be transformed.
 * The values of the coefficients are passed back to the main
 * program in the variables x, y, and z, which are reference parameters.
 */
void getCoordinates(double & x, double & y, double & z) {
   std::cout << "Enter the Cartesian Coordinates to be transformed:" << std::endl;
   x = getNumber("x: ") ;
   y = getNumber("y: ") ;
   z = getNumber("z: ") ;
}

/*
 * Function: getNumber
 * Usage: double x = getNumber(prompt);
 * ----------------------------------
 * Asks the user for an input, if the input is not a number it
 * keeps asking until the user enters a number.
 *
 * The given "message" string is printed before reading the value.
 */
double getNumber(std::string message){
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

/*
 * Function: printPolarCoordinates
 * Usage: printPolarCoordinates(x, y, z);
 * ----------------------------------
 * This function is responsible of transforming the given
 * Cartesian Coordinates (x, y, z) to Polar Coordinates
 * using the appropriate operations, and then prints the
 * resulting Polar Coordinates in the Console Window.
 */
void printPolarCoordinates(double x, double y, double z){
    double r;
    double theta;
    double fi;

    r = sqrt(pow(x,2.0) + pow(y, 2.0) + pow(z, 2.0));
    theta = atan2(y, x); // atan2 deals with the different cases that arise from the different values of x and y that can be received.
    if (z==0) fi=0;
    else fi = acos(z/r);

    std::cout << " " << std::endl;
    std::cout << "For Coordinates (" << x << ", " << y << ", " << z << "): " << std::endl;
    std::cout << "  r = " << r << std::endl;
    std::cout << "  theta = " << theta << std::endl;
    std::cout << "  fi = " << fi << std::endl;

}

/*
 * Function: atan2
 * Usage: theta = atan2(y, x);
 * ----------------------------------
 * atan2 computes the value of theta when transforming to poolar coordinates.
 * Theta is defined as a tan(y/x), and has different values depending on the
 * given x and y. This function returns the appropriate value for theta, for any x and y given.
 */
double atan2(double y, double x){
    double result;

    if (x>0) result = atan(y/x);
    else if(x<0 && y>=0) result = atan(y/x) + M_PI;
    else if(x<0 && y<0) result = atan(y/x) - M_PI;
    else if(x==0 && y>0) result = M_PI / 2.0;
    else if (x==0 && y<0) result = - M_PI / 2.0;
    else result =0;

    return result;
}
