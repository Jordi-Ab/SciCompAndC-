#include "WaveProblem.hpp"

WaveProblem::WaveProblem(const double speed,
                         const Vector* x_grid,
                         const Vector* y_grid){
    _speed = speed;
    _xgrid = new Vector(*x_grid);
    _ygrid = new Vector(*y_grid);

    // Initialize the Interior Discrete
    // Laplacian Operator Matrix.
    initInteriorLaplacian();

}

WaveProblem::~WaveProblem(){
    delete _xgrid;
    delete _ygrid;
    delete _L;
}


void WaveProblem::ComputeF( const double t, const Vector& u, Vector& f )const{

    // Compute F using the interior values, and interior Laplacian Matrix
    f = ( (*_L)*u )*( _speed*_speed );

}

Matrix WaveProblem::getInteriorValues(Matrix m){
    int rows = m.GetNumberOfRows()-2;
    int cols = m.GetNumberOfColumns()-2;

    Matrix interior_m( rows, cols );

    for (int r=1; r<=rows; r++){
        for (int c=1; c<=cols; c++){
            interior_m(r,c) = m(r+1,c+1);
        }
    }
    return interior_m;
}

void WaveProblem::initInteriorLaplacian(){

    int rows = _xgrid->GetSize()-2;
    int cols = _ygrid->GetSize()-2;
    ChebyshevDifferentiationLibrary cheby;

    // Complete Chebyshev Second Order Diff Matrix.
    Matrix Dx_2 = cheby.SecondOrderDifferentiationMatrix(*_xgrid);

    // Interior Chebyshev Second Order Diff Matrix.
    // i.e. Get rid of first and last row and column of Dx_2
    Matrix interior_Dx2 = getInteriorValues(Dx_2);

    // Complete Chebyshev Second Order Diff Matrix.
    Matrix Dy_2 = cheby.SecondOrderDifferentiationMatrix(*_ygrid);

    // Interior Chebyshev Second Order Diff Matrix.
    // i.e. Get rid of first and last row and column of Dy_2
    Matrix interior_Dy2 = getInteriorValues(Dy_2);

    Matrix Ix = cheby.eye(rows); // Identity Matrix
    Matrix Iy = cheby.eye(cols); // Identity Matrix

    // Discrete Laplacian is calculated with Kronecker products.
    _L = new Matrix( pow(rows,2), pow(cols,2) );
    *_L = interior_Dx2.KroneckerProduct(Iy) + Ix.KroneckerProduct(interior_Dy2);

}

