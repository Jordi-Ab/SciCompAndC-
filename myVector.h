/*
This is a class that suports scientific operations between vectors, like dot product,
substracting one vector from another, multiplication of vectors and matrices, etc.
*/

#ifndef _myVector_h
#define _myVector_h

#include <iostream>
#include <string>

class myVector{
	
public:
	myVector(int size);
	~myVector();
	int size();
	bool isEmpty();
	void clear();
	double getAt(int index);
	double setAt(int index);
	std::string toString();

private:

	/* Constants */
	//static const int INITIAL_CAPACITY = 100;
	
	/* Instance variables */
	double *elements; // A dynamic array of the elements
	int capacity; // The allocated size of the array
	int count; // The number of elements in use

	/* Private method prototypes */
	//void expandCapacity();


};
#endif
