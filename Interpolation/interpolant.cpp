#include "interpolant.hpp"

//PUBLIC SECTION:

Interpolant::Interpolant(const double* nodes,
                         const double* values,
                         const int n_nodes){

    this->nodes = nodes;
    this->values = values;
    this->degree = n_nodes-1;

}


void Interpolant::Evaluate(const double* xi, int n_points, double* p) const{
    for (int point=0; point<n_points; point++){
        evaluatePn(point, xi[point], p);
    }
}


//PRIVATE SECTION:

Interpolant::Interpolant(){

}

void Interpolant::evaluatePn(int point, double x, double* pns) const{
    pns[point] = 0.0;
    for(int j=0; j<this->degree+1; j++){
        double L = evaluateL(j, x);
        pns[point] += this->values[j]*L;
    }
}

double Interpolant::evaluateL(int index, double x) const{
    double L = 1.0;
    for (int i=0; i<this->degree+1; i++){
        if(index != i){
            L *= (x - this->nodes[i])/(this->nodes[index]-this->nodes[i]);
        }
    }
    return L;
}

