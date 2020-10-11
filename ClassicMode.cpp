/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "ClassicMode.h"

//Constructor. No data is needed, so constructor does nothing.
ClassicMode::ClassicMode() {}

//Destructor. No data is stored, so nothing needs deleting and the destructor does nothing.
ClassicMode::~ClassicMode() {}

//Checks for neighbors of a cell strictly within the bounds of the grid.
int ClassicMode::getNeighborsOfCell(Grid* gridWithCell, int row, int column) {
  //Sets variables for number of neighbors and the bounds to check for the given cells.
  int neighborCount = 0;
  int minBoundHeight = 0;
  int minBoundWidth = 0;
  int maxBoundHeight = gridWithCell->getHeight() - 1;
  int maxBoundWidth = gridWithCell->getWidth() - 1;

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

  //Iterates through each cell in the grid within the bounds set above (the neighbors)
  for(int i = minBoundHeight; i <= maxBoundHeight; ++i) {
    for(int j = minBoundWidth; j <= maxBoundWidth; ++j) {
      //If a cell is found alive (and that cell being checked in the loop is not the cell being searched for neighbors), the neighbors counter increases by one.
      if(!(i == row && j == column) && gridWithCell->getCell(i, j).isAlive()) {
        neighborCount++;
      }
    }
  }
  //The neighbor count is returned.
  return neighborCount;
}
