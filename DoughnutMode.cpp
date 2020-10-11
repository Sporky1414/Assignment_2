/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "DoughnutMode.h"

//Constructor. No data is needed, so constructor does nothing.
DoughnutMode::DoughnutMode() {}

//Destructor. No data is stored, so nothing needs deleting and the destructor does nothing.
DoughnutMode::~DoughnutMode() {}

//Checks for neighbors that are on the opposite side of the grid from where it is, should the cell be on the edge, in addition to standard neighbors.
int DoughnutMode::getNeighborsOfCell(Grid* gridWithCell, int row, int column) {
  //Creates a neighbor counter and sets the bounds of the search to the rows above/below the cell being checked and the columns to the right/left of that same cell.
  //If the bound is not a valid array index, it will be fixed shortly.
  int neighborCount = 0;
  int minBoundHeight = row - 1;
  int minBoundWidth = column - 1;
  int maxBoundHeight = row + 1;
  int maxBoundWidth = column + 1;

  //Iterates through the bounds, even if they go outsdie the array index.
  for(int i = minBoundHeight; i <= maxBoundHeight; ++i) {
    for(int j = minBoundWidth; j <= maxBoundWidth; ++j) {
      //Sets temporary variables containing the iterators corresponding to if they are set to the array's height or width indecies.
      int tempRow = i;
      int tempColumn = j;

      //If the column pointer is currently pointed ouside the array on the left, it is pointed to the edge of the array on the right.
      if(tempColumn < 0) {
        tempColumn = gridWithCell->getWidth() - 1;
      //Otherwise, the column pointer is pointed to the edge of the array on the left, should it be pointed to the outside of the array on the right
      } else if(tempColumn >= gridWithCell->getWidth()) {
        tempColumn = 0;
      }

      //If the row pointer is currently pointed outside the array on top, it is pointed to the edge of the array on the bottom.
      if(tempRow < 0) {
        tempRow = gridWithCell->getHeight() - 1;
      //Otherwise, the row pointer is pointed to the edge of the array on top, should it be pointed ot the outside of the array on the bottom.
      } else if(tempRow >= gridWithCell->getHeight()) {
        tempRow = 0;
      }

      //The cell coordinates, which were in bounds, are now checked to see if it is alive.
      //If it is (and the cell being checked now is not the cell being searched for neighbors), the neighbors counter is incremented.
      if(!(tempColumn == column && tempRow == row) && gridWithCell->getCell(tempRow, tempColumn).isAlive()) {
        neighborCount++;
      }
    }
  }
  //The neighbors counter is returned.
  return neighborCount;
}
