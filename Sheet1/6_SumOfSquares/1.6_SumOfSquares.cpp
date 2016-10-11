/*
 * This program computes de sum of squares from 1 to n.
 * n is given by the user.
 *
 * Comment:
 *  I'll make this by two different approaches, there is a formula
 *  for the sum of squares, obviously using the formula is
 *  more computationally efficient. But I'll also do it using a
 *  for loop just for the purpose of the excercise.
*/

#include <iostream>
#include <cmath>

int getNumber();
int computeWithFormula(int n);
int computeWithLoop(int n);

int main(){
    //int n = getNumber();
    //int n;
    int result;
    // std::cout << "Enter n: ";
    // std::cin >> n;
    int n = getNumber();
    bool useFormula= false; // Set to True if you want to compute the sum using the formula.
    if (n >= 100 || useFormula){
        std::cout << "Computed using the formula. " << std::endl;
        result = computeWithFormula(n);
    }else{
        std::cout << "Computed using a loop. " << std::endl;
        result = computeWithLoop(n);
    }

    std::cout << "Sum of Squares from 1 to " << n << " = " << result << std::endl;

    return 0;
}


int getNumber(){
    int input;
    while (true){
        std::cout << "Enter n: ";
        std::cin >> input;
        if (!std::cin.fail()) break;
        std::cout << "Not an integer, try again." << std::endl;
        std::cin.clear();
        std::cin.ignore();

    }
    return input;
}

int computeWithLoop(int n){
    int sum = 0;
    for (int i=1; i<=n; i++){
        sum += pow(i,2);
    }
    return sum;
}

int computeWithFormula(int n){
    return (n*(n+1)*(2*n+1))/6;
}




