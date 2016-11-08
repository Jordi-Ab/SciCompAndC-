//
//  main.cpp
//  randoms
//
//  Created by Jordi on 11/5/16.
//  Copyright © 2016 Beverido. All rights reserved.
//

#import <iostream>
#include <stdlib.h>
#include <cmath>
#include <string>
//#include "random.cpp"
using namespace std;

static void initRandomSeed() {
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(NULL)));
        initialized = true;
    }
}

string invert_string(string str){
    string new_string = "";
    for (int i=(int)str.length()-1; i>=0; i--){
        char ch = str[i];
        new_string += ch;
    }
    return new_string;
    
}

int MyRandom(){
    int r = rand();
    string str = to_string(r);
    string inverted_str = invert_string(str);
    int rand = atoi(inverted_str.c_str());
    return rand;
}

double randomReal(double low, double high) {
    initRandomSeed();
    double d = MyRandom() / (double(RAND_MAX) + 1);
    double s = d * (high - low);
    return low + s;
}

int randomInteger(int low, int high) {
    initRandomSeed();
    double d = randomReal(0,1) / (double(RAND_MAX) + 1);
    double s = d * (high - low+1.0);
    return int(floor(low + s)+low);
}

int myRandomInteger(){
    int r = rand();
    string str = to_string(r);
    char last_value = str[str.length()-1];
    int l = last_value - 48;
    
    if (l <= 1) l+=2;

    return l;
}

int randomInteger2(int low, int high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    return std::floor( ( high - low + 1.0 ) * d ) + low;
}


int main(){
    //int rand = randomInteger(-9,9);
    srand(int(time(NULL)));
    int r = myRandomInteger();
    cout << "My Random =" << r << endl;
    return 0;
}




