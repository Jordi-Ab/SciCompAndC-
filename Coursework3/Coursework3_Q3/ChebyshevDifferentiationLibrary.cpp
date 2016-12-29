#include "ChebyshevDifferentiationLibrary.hpp"

ChebyshevDifferentiationLibrary::ChebyshevDifferentiationLibrary(){}

Matrix ChebyshevDifferentiationLibrary::FirstOrderDifferentiationMatrix(const Vector& grid){
    int n = grid.GetSize()-1;
    Matrix M(n+1,n+1);
    for (int i=0; i<=n; i++){
        double xi = grid.Read(i);
        for (int j=0; j<=n; j++){
            double xj = grid.Read(j);
            double entry = 0;
            if(i==0 && j==0){
                entry = (2*pow(n,2.0) + 1)/6.0;
            }else if(i==n && j==n){
                entry = - (2*pow(n,2.0) + 1)/6.0;
            }else if (i==j){
                entry = -xj / ( 2*( 1-pow(xj,2.0) ) );
            }else{
                double ci = (i==0 || i==n) ? (2.0):(1.0);
                double cj = (j==0 || j==n) ? (2.0):(1.0);
                entry = (ci/cj) * ( pow(-1, i+j) / (xi - xj) );
            }
            M(i+1, j+1) = entry;
        }
    }
    return M;
}

Matrix ChebyshevDifferentiationLibrary::SecondOrderDifferentiationMatrix(const Vector& grid){
    int n = grid.GetSize()-1;
    Matrix M(n+1, n+1);
    for (int i=0; i<=n; i++){
        double xi = grid.Read(i);
        for (int j=0; j<=n; j++){
            double xj = grid.Read(j);
            double entry = 0;
            // First fill-in values at the boundaries
            if ( (i==0 && j==0) || (i==n && j==n) ){
                entry = ( pow(n,4) - 1 )/15.0;
            }
            // Then fill-in values at the first row
            else if (i==0){
                double cj = (j==0 || j==n) ? (2.0):(1.0);
                double c = pow(-1,j)/cj;
                double num = ( 2*(n*n) + 1 )*(1-xj) - 6;
                double den = (1 - xj)*(1 - xj);
                entry = (2/3.0)*c*(num / den);
            }
            // Then fill-in values at the last row
            else if (i == n){
                double cj = (j==0 || j==n) ? (2.0):(1.0);
                double c = pow( -1,(j+n) )/cj;
                double num = ( 2*(n*n) + 1 )*(1+xj) - 6;
                double den = (1 + xj)*(1 + xj);
                entry = (2/3.0)*c*(num / den);
            }
            // Then fill-in values at the diagonal
            else if (i==j){
                double num = ( (n*n)-1 )*( 1-(xi*xi) ) + 3;
                double den = 3*( pow( ( 1-(xi*xi) ),2.0) );
                entry = - num/den;
            }
            // At last, fill-in the rest of the values.
            else{
                double cj = (j==0 || j==n) ? (2.0):(1.0);
                double c =  pow( -1,(i+j) ) / cj;
                double num = (xi*xi) + (xi*xj) - 2;
                double den = ( 1-(xi*xi) )*pow( (xi-xj),2.0 );
                entry = c*(num / den);
            }
            M(i+1, j+1) = entry;
        }
    }
    return M;
}
