#include "GameMode.h"

GameMode::GameMode() {}

GameMode::~GameMode() {}

Grid* GameMode::createNewGridFromOldGrid(Grid* oldGrid) {
  Grid* tempGrid = new Grid(oldGrid);
  for(int i = 0; i < tempGrid->getHeight(); ++i) {
    for(int j = 0; j < tempGrid->getWidth(); ++j) {
      int neighborCount = getNeighborsOfCell(oldGrid, i, j);
      if(neighborCount <= 1 || neighborCount >= 4) {
        tempGrid->killCell(i, j);
      }
      if(neighborCount == 3) {
        tempGrid->createCell(i, j);
      }
    }
  }
  return tempGrid;
}
