/*
 * conways_game_of_life.c
 * Foraynia Wu / SID: 913241587
 * A list of function decinations used to determine how the 
 * game GAME OF LIFE goes 
 */

#include "conways_game_of_life.h"

#include <stdio.h>
#include <stdlib.h>


/*
 * Input:
 *      int num_rows, the number of rows in the game
 *      int num_cols, the number of cols in the game
 * Output:
 *      Returns a BinaryMatrix* that corresponds to the
 *      first generation game state
 * Summary:
 *      Returns the game state of the first generation
 */
BinaryMatrix* FirstGeneration(int num_rows, int num_cols, List* seed_cells) {
    int i;
    int x, y;
    BinaryMatrix* M;
    M = ConstructBinaryMatrix(num_rows, num_cols);
    for (i = 0; i < seed_cells->size; i +=1){
        x = seed_cells->head->data.x;
        y = seed_cells->head->data.y;
        UpdateEntry(M, x, y, 1);
        seed_cells->head = seed_cells->head->next;
    };
    return M;
}

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 * Output:
 *      Returns a BinaryMatrix*, a pointer to a game state
 * Summary:
 *      Calculates the game state of the generation directly
 *      after *generation and returns it
 */

BinaryMatrix* NextGeneration(BinaryMatrix* generation) {
    int i, j, rows, cols, number_of_living_neighbors;
    Coordinate C;
    List* neighborcells;
    BinaryMatrix* M;
    rows = generation->num_rows;
    cols = generation->num_cols;
    M = ConstructBinaryMatrix(rows, cols);
    for (i = 0; i < rows; i += 1){
        for (j = 0; j < cols; j += 1){
            C = ConstructCoordinate(i, j);
            neighborcells = NeighboringCells(C, generation); 
            number_of_living_neighbors = LivingNeighbors(generation, neighborcells);
            if ( number_of_living_neighbors == 3){
                UpdateEntry(M, i, j, 1);
            } else if (number_of_living_neighbors ==2 && generation -> data [i][j]==1){
                UpdateEntry(M, i, j, 1);
            } else if (number_of_living_neighbors ==2 && generation -> data [i][j]==0){
                UpdateEntry(M, i, j, 0);
            } else if (number_of_living_neighbors <= 1){
                UpdateEntry(M, i, j, 0);
            } else if (number_of_living_neighbors >= 4){
                UpdateEntry(M, i, j, 0);
            }
        }
    }
    return M;
}

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 *      Coordinate coord, a cell of the game state
 * Output:
 *      Returns true if the cell is Live
 * Summary:
 *      Checks if coord is a valid index of *generation and
 *      its corresponding cell is Live
 */
int Live(BinaryMatrix* generation, Coordinate coord) {
    int x, y;
    x = coord.x;
    y = coord.y;
    if (x < generation->num_rows && x >= 0 && y < generation->num_cols && y >= 0){
        if (generation->data[x][y] == 1){
            return 1;
        } else{
            return 0;
        }
    } else{
        return 0;
    }
}

/*
 * Input:
 *      Coordinate coord, a cell of the game state
 *      BinaryMatrix* generation, a pointer to a game state
 * Output:
 *      Returns a List* to a List of neighboring cells
 * Summary:
 *      Calculates neighboring cells of *generation at coord and
 *      returns them as a List
 */
List* NeighboringCells(Coordinate coord, BinaryMatrix* generation) {
    List* result = ConstructList();
    int i, j;
    if (result == (List*) NULL) {
        printf("Error in NeighboringCells: List construction failed\n");
        exit(EXIT_FAILURE);
    }
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            Coordinate coord_neighbor = ConstructCoordinate(coord.x + i, coord.y + j);
            if (IsNeighbor(coord, coord_neighbor) && IsMatrixIndex(generation, coord.x + i, coord.y + j)) {
                PushFrontList(result, coord_neighbor);
            }
        }
    }
    return result;
}

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 *      List* neighbors, a List of neighbors of a coordinate
 * Output:
 *      Returns the number of neighboring cells that are Live
 * Summary:
 *      Counts the number of Coordinates in *neighbors that
 *      correspond to live cells in *generation
 */
int LivingNeighbors(BinaryMatrix* generation, List* neighbors) {
    int i;
    int livingcells = 0;
    for (i = 0; i < neighbors->size; i+=1){
        if (Live(generation, neighbors->head->data)){
            livingcells += 1;
        } 
        neighbors->head = neighbors->head->next;
    }
    return livingcells;
}

/*
 * Input:
 *      BinaryMatrix* generation, a pointer to a game state
 *      FILE* fp, a file opened for writing
 * Summary:
 *      Prints the game state of *generation to *fp
 */
void PrintGeneration(BinaryMatrix* generation, FILE* fp) {
    int i, j;
    for (i = 0; i < generation->num_rows; i++) {
        for (j = 0; j < generation->num_cols; j++) {
            if (Live(generation, ConstructCoordinate(i, j))) {
                fprintf(fp, "#");
            } else {
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
    return;
}
