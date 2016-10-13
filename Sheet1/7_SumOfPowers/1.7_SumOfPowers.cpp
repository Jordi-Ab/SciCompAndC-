
/*
 * This program computes de sum of powers from 1 to n.
 * Say, the user gives an n and an m, and the program computes
 * (1^m) + (2^m) + ... + (n^m)
 * n is given by the user.
 *
*/

#include <iostream>
#include <cctype>
#include <cmath>
#include <string>

int getNumber(std::string message);
int computeSumOfPowers(int n, int m);
bool getYesOrNo();

int main(){
    int result;

    while (true){
        std::cout << " "<< std::endl;
        int n = getNumber("Enter n (last value of the summation): ");
        int m = getNumber("Enter m (power at which the numbers will be raised): ");
        result = computeSumOfPowers(n, m);
        std::cout << "Sum of number raised to" << m << ", from 1 to " << n << " = " << result << std::endl;
        std::cout << "Do you want to perform another calculation?" << std::endl;
        bool no = getYesOrNo();
        if (no) break;
    }
    return 0;
}

bool getYesOrNo(){ // Buggy function.
    bool choice;
    std::string line;
    while (true){
        std::cout <<  "Yes or No: ";
        getline(std::cin, line);
        if ((int) line.length() > 0) {
            char first = tolower(line[0]);
            if (first == 'y') {
                choice = true;
                break;
            } else if (first == 'n') {
                choice = false;
                break;
            }
        }
        std::cout << "Invalid Yes or No answer, try again." << std::endl;
        line = "";
    }
    return choice;
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

int computeSumOfPowers(int n, int m){
    int sum = 0;
    for (int i=1; i<=n; i++){
        sum += pow(i,m);
    }
    return sum;
}
