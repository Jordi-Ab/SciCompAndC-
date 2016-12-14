#include <iostream>
#include "Vector.cpp"
#include "Matrix.cpp"

int main(){
    Vector v(5);
    v[0] = 1.2; v[1] = 3.2;
    v[2] = 5.3; v[3] = 1.6;
    v[4] = 6.6;

    Matrix M(4,4);
    M(1,1) = 1.3; M(1,2) = 5.2; M(1,3) = 4.3;M(1,4) = 4.3;
    M(2,1) = 3.4; M(2,2) = 3.9; M(2,3) = 2.7;M(2,4) = 4.3;
    M(3,1) = 6.7; M(3,2) = 7.3; M(3,3) = 8.6;M(3,4) = 4.3;
    M(4,1) = 7.7; M(4,2) = 8.3; M(4,3) = 9.6;M(4,4) = 7.3;

    std::cout << "vector :" << std::endl;
    std::cout << v << std::endl;
    std::cout << "Size of v: " << v.GetSize() << std::endl;
    std::cout << "Entry 3 of v:" << std::endl;
    std::cout << v(3) << std::endl;

    std::cout << "" << std::endl;
    std::cout << "Matrix :" << std::endl;
    std::cout <<  M << std::endl;
    std::cout << "Rows of M: " << M.GetNumberOfRows() << std::endl;
    std::cout << "Cols of M: " << M.GetNumberOfColumns() << std::endl;



}
