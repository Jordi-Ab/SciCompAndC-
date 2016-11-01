#import <cmath>


/*
Function: findPivot
Usage: int pivot = findPivot(matrix, position, size);
-------------------------------------------------------------
* Assumes its working with square matrices.

Receives:
	.A matrix
	."position" -> Position of the initial pivot, 
		nameley initial pivot is @ (position, position).
	."size" -> Total number of rows and columns in the matrix.

Given the current position (row and col), it will go through the remaining
rows from this position down each row, leaving column fixed at position.

Returns: An integer that corresponds to the row index where the biggest entry
in absolute value is located in that column.

Ex:
int pivot = findPivot(matrix, 0, 4);

Matrix:
| 0  2 -1  6 |
| 1  0  2  1 |
|-1  0  3 -5 |
| 2  1  0  2 |
 
For column 0, pivot is located at row 4.
Hence, pivot = 4.
*/
int findPivot(double** matrix, int position, int size){
	double pivot = std::abs(matrix[position][position]);
	int pivot_index = position;
	for (int row=position+1; row<size; row++){
		double possible_pivot = std::abs(matrix[row][position]);
		if (possible_pivot > pivot){
				pivot = possible_pivot;
				pivot_index = row;
		}
	}
	return pivot_index;
}

/*
Function: swapRows
Usage: swapRows(a_matrix, 0, 3);
-------------------------------------------------------------
No return value. Mutates the given matrix.
Receives:
	. A matrix
	. "row1_index" -> Index of the first row to be swaped.
	. "row2_index" -> Index of the second row to be swaped.
Simply swaps row1 with row2. That is, puts row2 in the 
position of row1, and row1 in the position of row2.
*/

void swapRows(double** matrix, int row1_index, int row2_index){
	double* temp = matrix[row1_index];
	matrix[row1_index] = matrix[row2_index];
	matrix[row2_index] = temp;
}

