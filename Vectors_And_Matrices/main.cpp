#include <iostream>
#include "myVector.hpp"

int main(){
    myVector v;
    v.insertAt(0,1);
    v.insertAt(1,2);
    v.insertAt(2,3);
    v.insertAt(3,4);
    v.insertAt(4,5);
    std::cout << "v = " << v.toString() << std::endl;

    myVector v2(5);
    v2[0] = 2.2;
    v2[1] = 3.6;
    //v2.insertAt(2,4.1);
    //v2.insertAt(3,2.1);
    //v2.insertAt(4,3.4);
    std::cout << "v2 = " << v2.toString() << std::endl;


    v = v2;
    std::cout << "v = " << v.toString() << std::endl;
    v2[3] = 0;
    std::cout << "v2 = " << v2.toString() << std::endl;
    std::cout << "v = " << v.toString() << std::endl;
    return 0;
}
