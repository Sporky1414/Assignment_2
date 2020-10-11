/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "MirrorMode.h"

//Constructor. No data is needed, so constructor does nothing.
MirrorMode::MirrorMode() {}

//Destructor. No data is stored, so nothing needs deleting and the destructor does nothing.
MirrorMode::~MirrorMode() {}

//Checks for neighbors that are reflections near where it is, should the cell be on the edge, in addition to standard neighbors.
int MirrorMode::getNeighborsOfCell(Grid* gridWithCell, int row, int column) {
  //Sets variables for number of neighbors and the bounds to check for the given cells.
  int neighborCount = 0;
  int minBoundHeight = 0;
  int minBoundWidth = 0;
  int maxBoundHeight = gridWithCell->getHeight() - 1;
  int maxBoundWidth = gridWithCell->getWidth() - 1;

  //Sets booleans for if the cell being checked is on an edge and on a corner
  bool onEdge = false;
  bool corner = false;

  //If the row is not on top, the minimum row bound for the neighbor check is the row on top of the cell being checked.
  //Otherwise, the top row (where the cell is) is the minimum row bound.
  if(row != 0) {
    minBoundHeight = row - 1;
  }

  //If the row is not on the bottom, the maximum row bound for the neighbor check is the row below the cell being checked.
  //Otherwise, the bottom row (where the cell is) is the maximum row bound.
  if(row != maxBoundHeight) {
    maxBoundHeight = row + 1;
  }

  //If the column is not all the way to the left, the minimum column bound for the neighbor check is the column to the left of the cell being checked.
  //Otherwise, the leftmost column (where the cell is) is the minimum column bound.
  if(column != 0) {
    minBoundWidth = column - 1;
  }

  //If the column is not all the way to the right, the maximum column bound for the neighbor check is the column to the right of the cell being checked.
  //Otherwise, the rightmost column (where the cell is) is the maximum column bound.
  if(column != maxBoundWidth) {
    maxBoundWidth = column + 1;
  }

  //Checks if the cell being looked at is on an edge.
  if(row == 0 || column == 0 || row == gridWithCell->getHeight() - 1 || column == gridWithCell->getWidth() - 1) {
    onEdge = true;
    //If the cell is on the edge, it also checks for if the cell is on a corner (corners can not be off of an edge in a 2D array)
    if((row == 0 && column == 0) || (row == 0 && column == gridWithCell->getWidth() - 1) || (row == gridWithCell->getHeight() - 1 && column == 0) || (row == gridWithCell->getHeight() - 1 && column == gridWithCell->getWidth() - 1)) {
      corner = true;
    }
  }
  //Iterates throught the bounds of the array (each neighboring cell)
  for(int i = minBoundHeight; i <= maxBoundHeight; ++i) {
    for(int j = minBoundWidth; j <= maxBoundWidth; ++j) {

      //Checks if the cell at the specified coordinates given by the iterators is alive. Continues to the next iteration should the cell be dead.
      if(gridWithCell->getCell(i, j).isAlive()) {

        //If the cell is alive and is not the cell being searched, the neighbor counter is incremented.
        if(!(i == row && j == column)) {
          neighborCount++;
        //If the cell being checked is also the main cell being looked at for neighbors, it is checked to see if it is on the edge and not a corner.
        //If so, the neighbor count is incremented to account for its reflection on that edge and the rest of the loop is skipped.
        } else if (onEdge && !corner){
          neighborCount++;
          continue;
        //If the cell is a corner, the neighbor counter is upped by 3 (vertical, diaganol, horizontal reflections) and the rest of the loop is skipped.
        } else if(corner) {
          neighborCount += 3;
          continue;
        }

        //Checks for reflections should the cell being checked not be itself

        //Checks if the cell is on the edge and the cell being checked overall is not matching the one given by the iterators and is not corner.
        if(onEdge && !(corner && i == row && j == column)) {
          //If the cell is on the edge of the top/bottom of the grid, the neighbor counter is incremented to account for its reflection on that edge.
          if ((i == 0 || i == gridWithCell->getHeight() - 1) && i == row) {
            neighborCount++;
          //Otherwise, the cell counter is incremented should the cell be on the right/left edge of the array to account for its reflection on that edge.
          } else if ((j == 0 || j == gridWithCell->getWidth() - 1) && j == column) {
            neighborCount++;
          }
        }
      }
    }
  }
  //The neighbor counter is returned.
  return neighborCount;
}
