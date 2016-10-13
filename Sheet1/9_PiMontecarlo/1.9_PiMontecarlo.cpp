/*
 * This program approximates Pi = 3.1415...
 * using a Monte Carlo Simulation approach.
 *
 * Given an "n", generates n pairs of
 * random numbers (x,y) uniformly distributed on [0,1],
 * and calculates "m":
 * m = Number of times that (x^2 + y^2) < 1.
 *
 * The result is 4*(m/n).
 *
 */

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>


double randBetween(double low, double high);
double getInput(std::string message);
double computePi(int n);

int main(){
    int n;
    double almost_pi;
    /*
     * what rand() does is use an algorithm to generate a random number.
     * The problem is that the algorithm is always the same,
     * so the random number generated is always the same.
     * What I need is a way to "seed" that algorithm with a different number each time,
     * so that rand() will generate a different number.
     * The time(0) function returns the number of seconds that has elapsed since midnight, Jan 1, 1970.
     *  Every second, the value of time(0) will change, giving you a perfect way to seed the
     * random number generator with a different value each time you run your program.
     */
    srand(time(0)); // Initialize Random Seed
    n = getInput("Enter desired iterations of MonteCarlo: ");
    almost_pi = computePi(n);
    std::cout << "Pi is approximately equal to: " << almost_pi << std::endl;
}

/*
 * Function: computePi(int n);
 * Usage: f = computePi(n_times);
 * -------------------------------------------
 * Runs a Monte Carlo simulation n_times
 * to approximate the value of pi.
 *
 * Does this by:
 * Generating "n_times" pairs of random numbers (x,y)
 * uniformly distributed on [0,1].
 * Then calculating "m":
 * m = Number of times that (x^2 + y^2) < 1.
 *
 * The result is 4*(m/n)
 */
double computePi(int n){
    double x, y;
    int counter; // counter will keep track of the number of times (x^2 + y^2) < 1.
    for (int i = 0; i<=n; i++){
        x = randBetween(0,1);
        y = randBetween(0,1);
        if ((pow(x,2.0) + pow(y,2.0))<1) counter ++; // If (x^2 + y^2) < 1, then increase the counter.
    }
    return 4.0*(counter/(double) n);
}

/*
 * Function: randBetween
 * Usage: n = randBetween(low, high);
 * --------------------------------
 * Returns a double precision random number on the given
 * (low, high) interval.
 */
double randBetween(double low, double high) {
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (high - low);
    return low + s;
}

/*
 * Function: getInput
 * Usage: double x = getInput(prompt);
 * ----------------------------------
 * Asks the user for an input, if the input is not a number.
 * Keeps asking until the user enters a valid number.
 *
 * The given "message" string is prompted before reading the value.
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
