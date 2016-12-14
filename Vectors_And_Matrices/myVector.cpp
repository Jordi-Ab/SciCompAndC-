
#include <stdexcept>
#include <string>
#include <cmath>
#include <cassert>
#include <iomanip>
#include "myVector.hpp"

/*Constructor*/

myVector::myVector() {
    capacity = INITIAL_CAPACITY;
    count = 0;
    elements = new double[capacity]; // Defines a new vector of the given size.
}

myVector::myVector(int size) {
    capacity = size;
    count = size;
    elements = new double[capacity]; // Defines a new vector of the given size.
}

myVector::myVector(myVector& other_vector){
   this->capacity = other_vector.length();
   this -> count = other_vector.count;
   this->elements = new double [this->capacity];
   for (int i=0; i<other_vector.count; i++){
       this->elements[i] = other_vector.elements[i];
   }
}

/*Destructor. Frees the memory used by the array.*/
myVector::~myVector() {
    delete[] elements;
}

int myVector::length() const{
    return count;
}

bool myVector::isEmpty() const{
    return (count == 0);
}

void myVector::clear(){
    delete[] elements;
    count = 0;
    elements = new double[capacity];
}

double myVector::getAt(int index) const{
    if (index < 0 || index >= count) {
        throw std::runtime_error("getAt: index out of range");
    }
    return elements[index];
}
void myVector::setAt(int index, double element){
    if (index < 0 || index >= count) {
        throw std::runtime_error("setAt(): index out of range");
    }
    elements[index] = element;
}

void myVector::insertAt(int index, double elem) {
    if (count == capacity) expandCapacity();
    if (index < 0 || index > count) {
        throw std::runtime_error("insertAt: index out of range");
    }

    for (int i = count; i > index; i--) {
        elements[i] = elements[i - 1];
    }

    elements[index] = elem;
    count++;
}

std::string myVector::toString()const{
    std::string str = "[";
    for (int i=0; i<count-1; i++){
        str += std::to_string(elements[i]) + ", ";
    }
    str += std::to_string(elements[count-1]) + "]";
    return str;
}

//  OPERATORS

double& myVector::operator[](int index){
    if (index < 0 || index > count) {
        throw std::runtime_error("index out of range for operator []");
    }
   return elements[index];
}

const double& myVector::operator[](int index) const{
    if (index < 0 || index > count) {
        throw std::runtime_error("index out of range for operator []");
    }
   return elements[index];
}

bool myVector::operator !=(const myVector& v2) const {
    return !equals(v2);
}

myVector& myVector::operator =(const myVector& src) {
    if (this != &src) {
        if (elements != NULL) {
            delete[] elements;
        }
        deepCopy(src);
    }
    return *this;
}


// PRIVATE FUNCTIONS

void myVector::deepCopy(const myVector& src) {
    count = capacity = src.count;
    elements = (capacity == 0) ? NULL : new double[capacity];
    for (int i = 0; i < count; i++) {
        elements[i] = src.elements[i];
    }
}

bool myVector::equals(const myVector& v) const {
    if (this == &v) {
        return true;
    }
    if (length() != v.length()) {
        return false;
    }
    for (int i = 0, sz = length(); i < sz; i++) {
        if (getAt(i) != v.getAt(i)) {
            return false;
        }
    }
    return true;
}

void myVector::expandCapacity() {
    capacity *= 2;
    double* old_elements = elements;
    elements = new double[capacity];
    for (int i = 0; i < count; i++) {
        elements[i] = old_elements[i];
    }
    delete[] old_elements;
}
