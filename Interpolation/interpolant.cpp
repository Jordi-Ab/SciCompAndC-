#include "interpolant.hpp"

//PUBLIC SECTION:

Interpolant::Interpolant(const double* nodes,
                         const double* values,
                         const int n_nodes,
                         const bool barycentric_formula = false,
                         const bool chebyshev_interpolant=false){

    this->nodes = nodes;
    this->values = values;
    this->degree = n_nodes-1;
    this->barycentric_formula = barycentric_formula;
    this->chebyshev_interpolant = chebyshev_interpolant;

    if (this->barycentric_formula){
        weights = new double[degree+1];
        computeWeights();
    }else{
        weights = nullptr;
    }

}


void Interpolant::Evaluate(const double* xi, int n_points, double* p) const{
    for (int point=0; point<n_points; point++){
        if(barycentric_formula){
            p[point] = evaluateBarycentric(point, xi[point], p);
        }else{
            p[point] = evaluateLagrange(xi[point]);
        }
    }
}


//PRIVATE SECTION:

Interpolant::Interpolant(){

}

double Interpolant::evaluateLagrange(const double x) const{
    p = 0.0;
    for(int j=0; j<this->degree+1; j++){
        double L = getLj(j, x);
        p += this->values[j]*L;
    }
    return p;
}

double Interpolant::evaluateBarycentric(const double x) const{
    /*Left here.
    Still missing to correctly program this function.*/
    p = 0.0;
    for(int j=0; j<this->degree+1; j++){
        double L = getLj(j, x);
        p += this->values[j]*L;
    }
    return p;
}

double Interpolant::getLj(int j, const double x) const{
    double L = 1.0;
    for (int i=0; i<this->degree+1; i++){
        if(j != i){
            L *= (x - this->nodes[i])/(this->nodes[j]-this->nodes[i]);
        }
    }
    return L;
}

void Interpolant::computeWeights(){

    if(chebyshev_interpolant){
        computeWeightsAnalytically();
    }else{
        computeWeightsIterativeley();
    }
}

void Interpolant::computeWeightsAnalytically(){
    weights[0] = 0.5;
    for (int j=1; j<degree; j++){
        weights[j] = pow(-1.0, j);
    }
    weights[degree] = 0.5;
}

void Interpolant::computeWeightsIterativeley(){
    for ( int j=0; j<degree+1; j++ ){
    weights[j] = 1.0;
    // Product over index k
        for ( int k=0; k<degree+1; k++ ){
            if ( j != k ){
                weights[j] /=  (nodes[j] - nodes[k]) ;
            }
        }
    }
}

