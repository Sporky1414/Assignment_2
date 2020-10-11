/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "GameMode.h"

//Constructor. Doesn't need to setup anything.
GameMode::GameMode() {}

//Destructor. Doesn't need to delete anything
GameMode::~GameMode() {}

//Returns a pointer to a grid whose cells are killed/created based on their neighbors in the original grid passed as an argument.
Grid* GameMode::createNewGridFromOldGrid(Grid* oldGrid) {
  //Creates the new grid to store the new data. It is copied from oldGrid.
  Grid* tempGrid = new Grid(oldGrid);
  for(int i = 0; i < tempGrid->getHeight(); ++i) {
    for(int j = 0; j < tempGrid->getWidth(); ++j) {
      //Gets the number of neighbors at each cell in oldGrid.
      int neighborCount = getNeighborsOfCell(oldGrid, i, j);

      //If the cell has 1 or fewer neighbors, the corresponding cell in tempGrid is killed and a dead cell is left in place.
      //Dead cells remain dead in this situation. Same happens with 4 or greater neighbors.
      if(neighborCount <= 1 || neighborCount >= 4) {
        tempGrid->killCell(i, j);
      }
      //If the cell has 3 neighbors, the corresponding cell in tempGrid is created in the given spot (should one not be there already).
      if(neighborCount == 3) {
        tempGrid->createCell(i, j);
      }
      //Nothing happesn in cells with 2 neighbors for tempGrid.
    }
  }
  //The new grid, containing the neighbor-based changes, is returned.
  return tempGrid;
}
