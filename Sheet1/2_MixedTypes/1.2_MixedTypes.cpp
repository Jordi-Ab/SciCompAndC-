#include <iostream>
#include <cmath>

int main(){
    std::cout << "19/5 - 1.8 = " << 19/5 - 1.8 << std::endl;
    std::cout << "17/4.0 - 6.25 = " << 17/4.0 - 6.25 << std::endl;
    std::cout << "56 - 5*(56/5) = " << 56 - 5*(56/5) << std::endl;
    std::cout << "28/(14/4) = " << 28/(14/4) << std::endl;
    int exp1 = 1/4;
    double exp2 = 1.0/4.0;
    std::cout << "16.0**(1/4) - 16**(1.0/4.0) = " << pow(16,exp1) - pow(16,exp2) << std::endl;
}
