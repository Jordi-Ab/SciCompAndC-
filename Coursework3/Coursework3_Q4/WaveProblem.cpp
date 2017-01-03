#include "WaveProblem.hpp"

WaveProblem::WaveProblem(const double speed,
                         const Vector* x_grid,
                         const Vector* y_grid){
    _speed = speed;
    _xgrid = new Vector(*x_grid);
    _ygrid = new Vector(*y_grid);

    // Initialize the interior
    // Discrete Laplacian Operator Matrix.
    // (Interior to apply the Boundary Conditions.)
    initInteriorLaplacian();

}

WaveProblem::~WaveProblem(){
    delete _xgrid;
    delete _ygrid;
    delete _L;
}


void WaveProblem::ComputeF( const double t, const Vector& u, Vector& f )const{

    // Get the values of u that are not at boundary nodes.
    //Vector interior_u = getInteriorValues(u);

    // Compute F using the interior values, and interior Laplacian Matrix
    f = ( (*_L)*u )*( _speed*_speed );

    // Apply Boundary Conditions to get the complete result.
    // i.e. Zero-out nodes at boundaries
    //applyBoundaryConditions(interior_sol, f);
}

Vector WaveProblem::getInteriorValues(const Vector u) const{
    int Nx = _xgrid->GetSize()-2;
    int Ny = _ygrid->GetSize()-2;

    Vector interior_u( Nx*Ny );
    int interior_index = 0;

    // Iterate through the nodes that are not at the boundaries,
    // in Lexicographical ordering.
    for (int x_ix=1; x_ix<=Nx; x_ix++){
        for (int y_ix=1; y_ix<=Ny; y_ix++){
            int exterior_index = (x_ix*Ny) + y_ix;
            interior_u[interior_index] = u.Read(exterior_index);
            interior_index ++;
        }
    }
    return interior_u;
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

void WaveProblem::applyBoundaryConditions(const Vector interior_u, Vector& f) const{
    int Nx = _xgrid->GetSize();
    int Ny = _ygrid->GetSize();

    int interior_index = 0;
    // Iterate through the nodes in the mesh,
    // in Lexicographical ordering.
    for (int x_ix=0; x_ix<Nx; x_ix++){
        for (int y_ix=0; y_ix<Ny; y_ix++){
            int exterior_index = (x_ix*Ny) + y_ix;
            // Test if Node is at Boundary
            if( (x_ix == 0 || x_ix == Nx-1) || (y_ix == 0 || y_ix == Ny-1) ){
                // Node is at Boundary.
                f[exterior_index] = 0; // Apply Boundary Condition.
            }else{
                // Node is an interior Node.
                f[exterior_index] = interior_u.Read(interior_index);
                interior_index++;
            }
        }
    }
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

