#include <iostream>
#include <cmath>
#include "VecsAndMats.h"

/*
 * Function: tridiagonal
 * Usage: double** a_mat = tridiagonal(1,2,3,6);
 * ----------------------------------------------------
 * Receives:
 *  . m -> Double number, first entry of main diagonal.
 *  . u -> Double number, first entry of upper diagonal.
 *  . l -> Double number, first entry of lower diagonal.
 *  . size -> Size you want the square matrix to have.
 * Returns a tri-diagonal square matrix.
 *
 * i.e. Suppose given size = 6.
 * |m u 0 0 0 0|
 * |l m u 0 0 0|
 * |0 l m u 0 0|
 * |0 0 l m u 0|
 * |0 0 0 l m u|
 * |0 0 0 0 l m|
 */
double** tridiagonal(double m, double u, double l, int size);
double* jacobiSolve(double** A, double* b, double* initial_x, int size);
double* gauss_SeidelSolve(double** A, double* b, double* initial_x, int size);
double* sorSolve(double** A, double* b, double* initial_x, double omega, int size);
double* createB(int size);
double* zerosV(int size);

int main(){
    int n = 15; // Size of the system.
    int l = 1; // First entry of lower diagonal.
    int u = 1; // First entry of upper diagonal.
    int h = 2/(n + 1); // Mesh Size.
    int m = -2*(1+2*(h*h));

    double** K = tridiagonal(m,u,l,n);
    double* b = createB(15);
    double* init_x = zerosV(n);

    //double* x_jacobi = jacobiSolve(K, b, init_x, n);
    //printV(x_jacobi, n);

    //double* x_gauss_seid = gauss_SeidelSolve(K, b, init_x, n);
    //printV(x_gauss_seid, n);

    /*Sor method converges in the same # of iterations as Gauss-Seidel.
    Hence, there is a bug in the code.*/
    double omega = 1.527893;
    double* x_sor = sorSolve(K, b, init_x, omega, n);
    printV(x_sor, n);

    return 0;
}

double** tridiagonal(double m, double u, double l, int size){
    double** result = createMatrix(size, size);
    for (int r=0; r< size; r++){
        for (int c=0 ; c<size; c++){
            if ((c-r)==-1) result[r][c] = l;
            else if ((c-r)==0) result[r][c] = m;
            else if ((c-r)==1) result[r][c] = u;
            else result[r][c] = 0;
        }
    }
    return result;
}

double* createB(int size){
    double* b = new double[size];
    for(int entry=0; entry<size; entry++){
        if (entry%2 == 0){
            b[entry] = -1;
        }else{
            b[entry] = 0;
        }
    }
    return b;
}

double* zerosV(int size){
    double* v = new double[size];
    for(int entry=0; entry<size; entry++){
        v[entry] = 0;
    }
    return v;
}

