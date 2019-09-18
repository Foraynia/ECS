/*
 * coordinate.h
 * Foraynia Wu / SID: 913241587
 * A data structure modeling 2D integer Cartesian Coordinates
 */

#ifndef _COORDINATE_H_
#define _COORDINATE_H_

typedef struct {
    int x, y;
} Coordinate;

/*
 * Input:
 *      int x, an x-coordinate
 *      int y, a y-coordinate
 * Output:
 *      A Coordinate
 * Summary:
 *      Initializes a Coordinate to (x,y)
 */
Coordinate ConstructCoordinate(int x, int y);

/*
 * Input:
 *      Coordinate C1, a coordinate
 *      Coordinate C2, another coordinate
 * Output:
 *      true if C2 is a neighbor of C1, false otherwise
 * Summary:
 *      Checks if C1 and C2 are neighbors, that is, if they
 *      are in adjacent squares (including squares that are
 *      diagonally adjacent) and not equal
 */
int IsNeighbor(Coordinate C1, Coordinate C2);

/*
 * Input:
 *      Coordinate* C, a pointer to a Coordinate
 * Summary:
 *      Swaps the entries of the Coordinate pointed to by C
 */
void SwapCoordinates(Coordinate* C);

#endif  /* _COORDINATE_H_ */
