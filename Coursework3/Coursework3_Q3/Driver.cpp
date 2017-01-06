#include <iostream>
#include <cmath>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "ChebyshevGrid1d.hpp"
#include "ChebyshevDifferentiationLibrary.hpp"

// Exponential Function evaluated at a vector.
Vector f(const Vector& x);

int main(){
    Matrix A(2,2);
    A(1,1) = 1; A(1,2) = 3;
    A(2,1) = 2; A(2,2) = 4;

    Matrix u(3,1);
    u(1,1) = 1;
    u(2,1) = 2;
    u(3,1) = 3;

    Matrix M(4,2);
    M(1,1) = 1; M(1,2) = 5;
    M(2,1) = 2; M(2,2) = 6;
    M(3,1) = 3; M(3,2) = 7;
    M(4,1) = 4; M(4,2) = 8;

    Matrix A_sqrt = A*A;
    Matrix kroneck1 = u.KroneckerProduct(M);
    Matrix kroneck2 = M.KroneckerProduct(u);

    std::cout << "A^2:" << std::endl;
    std::cout << A_sqrt << std::endl;
    std::cout << "u (x) M:" << std::endl;
    std::cout << kroneck1 << std::endl;
    std::cout << "M (x) u: " << std::endl;
    std::cout << kroneck2 << std::endl;

    // Number of Gauss-Lobatto grid points.
    int n1 = 4;
    ChebyshevGrid1D grid(n1);
    std::cout << "Coordinates of a Gauss-Lobato grid with ";
    std::cout << n1+1 << " points: " << std::endl;
    std::cout << grid << std::endl;

    // Size of the Differentiation Matrix that will be used.
    int n2 = 40;

    // Instantiate Chebyshev object.
    ChebyshevDifferentiationLibrary chebyshev;

    // (n+1)x(n+1) Gauss–Lobatto nodes in the interval [-1,1].
    ChebyshevGrid1D mesh(n2);

    // (n+1)x(n+1) Second order Chebyshev Differentiation Matrix.
    Matrix D2 = chebyshev.SecondOrderDifferentiationMatrix(mesh);

    // f evaluated at mesh points.
    Vector ys = f(mesh);

    // Computation of the second derivative using a
    // second order Chebyshev differentiation Matrix.
    Vector second_deriv = D2*ys;

    // Second derivative of exp(x) is exp(x), so "ys" can also
    // work as the true value of the second derivative.
    double error = (ys - second_deriv).CalculateInfinityNorm();

    std::cout << "Error of the second derivative of exp(x), ";
    std::cout << "computed using a "<<n2+1<<"x"<<n2+1;
    std::cout << " Chebyshev second order differentiation matrix: " << std::endl;
    std::cout << "Error (inf-norm) = " << error << std::endl;

}

Vector f(const Vector& x){
    int n = x.GetSize();
    Vector result(n);
    for (int i=0; i<n; i++){
        result[i] = exp(x.Read(i));
    }
    return result;
}


