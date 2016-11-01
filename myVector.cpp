
#ifdef _MyVector_h

#include <stdexcept>
#include <string>

/*Constructor*/
myVector::myVector(int size) {
	dim = size;
   	count = 0;
   	elements = new ElemType[dim]; // Defines a new vector of the given size.
}

/*Destructor. Frees the memory used by the array.*/
myVector::~myVector() {
   	delete[] elements;
}

int myVector::size() {
	return count;
}

bool myVector::isEmpty() {
	return (count == 0)
}

void myVector::clear(){
	dim = size;
	delete[] elements;
   	count = 0;
   	elements = new ElemType[size];
}

double myVector::getAt(int index) {
	if (index < 0 || index >= count) {
		throw std::runtime_error("getAt: index out of range");
   	}
   	return elements[index];
}

double myVector::setAt(int index, double element) {
	if (index < 0 || index >= count) {
		throw std::runtime_error("getAt: index out of range");
   	}
   	return elements[index] = element;
}

std::string myVector::toString(){
	std::string = "";
	for (int i=0; i<SIZE; i++){
		if (vector[i]>=0 && vector[i]<10) string += "| ";
		else string += "|";
		string += vector[i] + "|\n";
	}
	return string;
}

