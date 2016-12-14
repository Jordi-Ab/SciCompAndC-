#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP


#include <iostream>
#include <string>

class myVector{

public:

// CONSTRUCTORS-DESTRUCTORS:
    myVector();
    myVector(int size);
    myVector(myVector& other_vector);
    ~myVector();

// FUNCTIONS:

    /*
     * Function: length
     * Usage: a_vector.length()
     * ------------------------
     * Returns the number of elements
     * inside a vector object.
    */
    int length() const;

    /*
     * Function: isEmpty
     * Usage: a_vector.isEmpty()
     * ------------------------
     * Returns true if the vector object
     * contains no elements.
    */
    bool isEmpty() const;

    /*
     * Function: clear
     * Usage: a_vector.clear()
     * ------------------------
     * Empties a vector object, and returns
     * it to its initial state.
    */
    void clear();

    /*
     * Function: insertAt
     * Usage: a_vector.insertAt(5, 10.5);
     * ------------------------
     * Inserts the given element "elem",
     * at the given position "index" inside
     * the vector object.
    */
    void insertAt(int index, double elem);

    /*
     * Function: getAt
     * Usage: a_vector.getAt(5);
     * ------------------------
     * Returns the element contained at the
     * given position "index", inside the vector,
     * in read only mode.
     * Raises an error if the vector doesn't contain
     * any value at the given index.
    */
    double getAt(int index) const;

    /*
     * Function: setAt
     * Usage: a_vector.setAt(5, 11.1);
     * ------------------------
     * Overwrites the element at the given
     * position "index", with the given value
     * "element".
     * Raises an error if the vector doesn't contain
     * any value at the given index.
    */
    void setAt(int index, double element);

    /*
     * Function: setAt
     * Usage: a_vector.toString();
     * ------------------------
     * Returns a string representation of the
     * vector object.
    */
    std::string toString() const;

// OPERATORS:

    /*
     * Operator: []
     * Usage: vec[index]
     * -----------------
     * Overloads [] to select elements from this vector.
     * This extension enables the use of traditional array notation to
     * get or set individual elements.
     * This method signals an error if the index is outside the array range.
     * The file supports two versions of this operator, one for const vectors
     * and one for mutable vectors.
    */
    double& operator [](int index);
    const double& operator [](int index) const;

    /*
     * Operator: =
     * Usage1: vector1 = vector2;
     * Usage2: a_vector[3] = 2.0;
     * ------------------------
     * Overwrites the elements of the vector
     * on the left side, with the elements of
     * the vector on the right side.
     * Raises an error if both vector don't have
     * the same length.
    */
    myVector& operator=(const myVector& src);

    bool operator !=(const myVector& v2) const;

private:

//CONSTANTS:
    static const int INITIAL_CAPACITY = 100;

//INSTANCE VARIABLES:
    double *elements; // A dynamic array of the elements
    int capacity; // The allocated size of the array
    int count; // The number of elements in use

//FUNCTIONS:
    void expandCapacity();
    void deepCopy(const myVector& src);
    bool equals(const myVector& v) const;


};

#endif // MYVECTOR_HPP
