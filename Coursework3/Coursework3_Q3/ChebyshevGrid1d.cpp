#include "ChebyshevGrid1d.hpp"

// Calls the specialized constructor of Vector(int size);
ChebyshevGrid1D::ChebyshevGrid1D(const int n):Vector(n+1){
    // This object was initializaed as a Vector, though
    // we can't overwrite its "mData" instance. But,
    // we can make "_nodes" to point to "this", that way we
    // can overwrite the data of "this" using "_nodes" pointer.
    _nodes = this;
    for (int j=0; j<this->GetSize(); j++){
        (*_nodes)[j] = cos(j*M_PI/n);
    }
}

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
