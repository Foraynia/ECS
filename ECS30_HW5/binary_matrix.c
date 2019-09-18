/*
 * binary_matrix.c
 * Foraynia Wu / SID: 913241587
 * This document defines all the functions needed
 * in the binary matrix sections
 */

#include "binary_matrix.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Input: 
 * 	num_rows, how many rows the matrix has
 *      num_cols, how many cols the matrix has
 * Output: 
 * 	A binary matrix
 * Summary:
 * 	Creates an empty binary matrix
 */
BinaryMatrix* ConstructBinaryMatrix(int num_rows, int num_cols) {
    int i;
    BinaryMatrix* M;
    if (num_rows <= 0 || num_cols <= 0){
        printf("Error in CreateMatrix: number of rows and columns must be positive\n");
        exit(0);
    }
    M = (BinaryMatrix *)malloc(sizeof(BinaryMatrix));
    M->data = (int **) malloc(num_rows * sizeof(int*));
    for (i = 0; i < num_rows; i += 1){
        M->data[i] = (int*) malloc(num_cols * sizeof(int));
    }
    M->num_rows = num_rows;
    M->num_cols = num_cols;
    return (M);
}

/*
 * Input:
 * 	M, a pointer to an existing binary matrix
 * Summary:
 * 	Cleans up the memory space for the matrix M
 */
void DeleteBinaryMatrix(BinaryMatrix* M) {
    int i;
    for (i = 0; i < M->num_rows; i += 1){
        free (M->data[i]);
    }
        free(M);	
}

/*
 * Input:
 * 	M, a pointer to a binary matrix
 * 	row, the x coordinate of the matrix
 * 	col, the y coordinate of the matirx
 * 	content, 1 means alive, 0 means dead
 * Summary:
 * 	Update the matrix M with the content given
 */
void UpdateEntry(BinaryMatrix* M, int row, int col, int content) {
    if (row >= M->num_rows || row < 0 || col >= M->num_cols || col < 0){
        printf("Error in UpdateEntry: index out of bounds\n");
        exit(0);
    } else if(content != 1 && content != 0){
        printf("Error in UpdateEntry: content must be 0 or 1\n");
        exit(0);
    } else {
        M->data[row][col] = content;
    }
}

/*
 * Input:
 * 	M, a pointer to a binary matrix
 * 	row, the index of row
 * 	col, the index of colume
 * Output:
 * 	A number
 * Summary:
 * 	Check if it is the correct index inside the matrix,
 * 	if yes, return 1 other wise it is not a correct index
 */
int IsMatrixIndex(BinaryMatrix* M, int row, int col) {
    if (row >= M->num_rows || col >= M->num_cols){
        return 0;
    } else if( M == NULL){
        printf("IsMatrixIndex Error: NULL parameter passed\n");
        exit(0);
    } else {
        return 1;
    }
}

/*
 * Input:
 * 	M, a pointer to a binary matrix
 * Summary:
 * 	Print out the content of this matrix
 */
void PrintMatrix(BinaryMatrix* M) {
    int i, j;
    for (i = 0; i < M->num_rows; i += 1){
        for (j = 0; j < M->num_cols; j += 1){
            printf("%d", M->data[i][j]);
        }
        printf("\n");
    }
}

