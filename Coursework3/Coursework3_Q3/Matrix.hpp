#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.hpp"
#include <iostream>

// Class adapted from Whiteley, Pitt-Francis
class Matrix
{

private:

  // Entries of matrix
  double** mData;

  // Dimensions
  int mNumRows, mNumCols; 

public:

  // Copy constructor
  Matrix(const Matrix& otherMatrix);

  // Specialised Constructor 
  Matrix(int numRows, int numCols);

  // Destructor
  ~Matrix();

  // Accessors
  int GetNumberOfRows() const;
  int GetNumberOfColumns() const;

  // 1-based indexing
  double& operator()(int i, int j);

  //Overloaded assignment operator
  Matrix& operator=(const Matrix& otherMatrix);

  // Unary +
  Matrix operator+() const;

  // Unary -
  Matrix operator-() const;

  // Binary + 
  Matrix operator+(const Matrix& m1) const;

  // Binary - 
  Matrix operator-(const Matrix& m1) const; 

  // Scalar multiplication
  Matrix operator*(double a) const;

  // Matrix Matrix multiplication
  /*    Written by Giordi Azonos     */
  Matrix operator*(const Matrix& m1) const;

  // Kroneker Product between two matrices.
  /*    Written by Giordi Azonos    */
  Matrix KroneckerProduct( const Matrix& m1) const;

  /*
   * Function: getColumn();
   * Usage: a_matrix.getColumn(index);
   *       Added by Giordi Azonos
   * -----------------------------
   * Returns the column at the given index
   * of this matrix as a new Vector object.
   * Uses 1-based indexing.
   */
  Vector GetColumn(int index) const;

  /*
   * Function: getRow();
   * Usage: a_matrix.getRow(index);
   *       Added by Giordi Azonos
   * -----------------------------
   * Returns the row at the given index
   * of this matrix as a new Vector object.
   * Uses 1-based indexing.
   */
  Vector GetRow(int index) const;

  // Determinant
  double CalculateDeterminant() const;

  // Declare vector multiplication friendship
  friend Vector operator*(const Matrix& m, 
                          const Vector& v);
  friend Vector operator*(const Vector& v, 
                          const Matrix& m);

  // Overridden << operator
  friend std::ostream& operator<<(std::ostream& output,
                        const Matrix& m);

};

// prototype signatures for friend operators
Vector operator*(const Matrix& m, const Vector& v);
Vector operator*(const Vector& v, const Matrix& m);

#endif
