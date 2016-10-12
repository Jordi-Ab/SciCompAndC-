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


double randomBetween(double low, double high);
static void initRandomSeed();

int main(){
    double x, y;
    for (int i = 0; i<=10000; i++){
        x = randomBetween(0,1);
        std::cout  << x << std::endl;
        //y = randomBetween(0,1);
    }

}


/*
 * Implementation notes: initRandomSeed
 * ------------------------------------
 * The initRandomSeed function declares a static variable that keeps track
 * of whether the seed has been initialized.  The first time initRandomSeed
 * is called, initialized is false, so the seed is set to the current time.
 */
static void initRandomSeed() {
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
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(NULL)));
        initialized = true;
    }
}

/*
 * Implementation notes: randomReal
 * --------------------------------
 * The code for randomReal is similar to that for randomInteger,
 * without the final conversion step.
 */
double randomBetween(double low, double high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (high - low);
    return low + s;
}
