/*
 * binary_matrix.h
 * Foraynia Wu / SID: 913241587
 * An implementation of a lists of functions using 
 * in binary matrix section
 */

#ifndef _BINARY_MATRIX_H_
#define _BINARY_MATRIX_H_

typedef struct{
	int num_rows;
	int num_cols;
	int** data;
} BinaryMatrix;

/*
 * Input:
 * 	num_wors, how many rows the matrix has
 * 	num_cols, how many cols the matrix has
 * Output:
 * 	A binary matrix
 * Summary:
 * 	Create an empty binary matrix
 */
BinaryMatrix* ConstructBinaryMatrix(int num_rows, int num_cols);

/*
 * Input:
 * 	M, a pointer to an existing binary matrx
 * Summary:
 * 	Cleans up the memory space for the matrix M
 */
void DeleteBinaryMatrix(BinaryMatrix* M);

/*
 * Input:
 * 	M, a pointer to a binary matrix
 * 	row, the x coordinate of the matirx
 * 	col, the y coordinate of the matirx
 * 	content, 1 means alive, 0 means dead
 * Summary:
 * 	Update the matrix M with the content given
 */
void UpdateEntry(BinaryMatrix *M, int row, int col, int content);

/*
 * Input:
 * 	M, a pointer to a binary matirx
 * 	row, the index of row
 * 	col, the index of colume
 * Output:
 * 	A number
 * Summary:
 * 	Check if it is the correct index inside the matrix, 
 * 	if yes, return 1 otherwise it is not a correct intdex
 */
int IsMatrixIndex(BinaryMatrix* M, int row, int col);

/*
 * Input:
 * 	M, a pointer to a binary matrix
 * Summary:
 * 	Print out the content of this matrix
 */
void PrintMatrix(BinaryMatrix *M);
#endif /* _BINARY_MATRIX_H_ */
