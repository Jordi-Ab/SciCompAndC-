#include "ChebyshevGrid1d.hpp"

ChebyshevGrid1D::ChebyshevGrid1D(const int n):Vector(n+1){
    // this object was initializaed as a Vector, though
    // we can't overwrite its "mData" instance. So
    // we can make "_nodes" to point to "this", so now we
    // can overwrite the data of "this" using "_nodes" pointer.
    _nodes = this;
    for (int j=0; j<this->GetSize(); j++){
        (*_nodes)[j] = cos(j*M_PI/n);
    }
}

/*ChebyshevGrid1D::~ChebyshevGrid1D(){
    delete _nodes;
}*/

std::ostream& operator<<(std::ostream& output, ChebyshevGrid1D& grid){

    output << "[";
    for (int i=0; i<grid.GetSize()-1; i++){
        output << grid.Read(i);
        output << ", ";
    }
    output << grid.Read(grid.GetSize()-1);
    output << "]" << std::endl;

    return output;
}
