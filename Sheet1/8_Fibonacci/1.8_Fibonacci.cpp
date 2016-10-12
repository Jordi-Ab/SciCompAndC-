/*
 * This program prints on the console screen the Fibonacci Squence:
 * 1,1,2,3,5,8,13,21,34,55,89,.... Until having n numbers, where n will be
 * given by the user, and is the number of iterations of the fibonacci sequence.
 * For example: n = 6 will print: 1, 1 ,2, 3, 5, 8.
 *
 */

#include <iostream>
#include <string>

// Function Prototypes declaration
int getNumber(std::string message);
int Fib(int n);

/* Main program */
int main() {
    std::cout << "This program prints the Fibonacci sequence on the screen." << std::endl;
    int n = getNumber("Number of desired iterations of the sequence: ");
    for (int i = 0; i < n; i++) {
        std::cout << Fib(i) << ", ";
    }
    std::cout << Fib(n) << std::endl; // Last term.
    return 0;
}

int getNumber(std::string message){
    int input;
    while (true){
        std::cout << message;
        std::cin >> input;
        if (!std::cin.fail()) break;
        std::cout << "Not an integer, try again." << std::endl;
        std::cin.clear();
        std::cin.ignore();
    }
    return input;
}

/*
 * Function: Fib
 * Usage: t = Fib(n);
 * ------------------
 * This function returns the nth term in the Fibonacci sequence
 * using a recursive implementation of the recurrence relation
 *
 *      Fib(n) = Fib(n - 1) + Fib(n - 2)
 */
int Fib(int n) {
    if (n < 2) return n;
    else return Fib(n - 1) + Fib(n - 2);
}
