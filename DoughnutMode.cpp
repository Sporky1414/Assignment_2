#include "DoughnutMode.h"

DoughnutMode::DoughnutMode() {}

DoughnutMode::~DoughnutMode() {}

int DoughnutMode::getNeighborsOfCell(Grid* gridWithCell, int row, int column) {
  int neighborCount = 0;
  int minBoundHeight = row - 1;
  int minBoundWidth = column - 1;
  int maxBoundHeight = row + 1;
  int maxBoundWidth = column + 1;
  for(int i = minBoundHeight; i <= maxBoundHeight; ++i) {
    for(int j = minBoundWidth; j <= maxBoundWidth; ++j) {
      int tempRow = i;
      int tempColumn = j;
      if(tempColumn < 0) {
        tempColumn = gridWithCell->getWidth() - 1;
      } else if(tempColumn >= gridWithCell->getWidth()) {
        tempColumn = 0;
      }
      if(tempRow < 0) {
        tempRow = gridWithCell->getHeight() - 1;
      } else if(tempRow >= gridWithCell->getHeight()) {
        tempRow = 0;
      }
      if(!(tempColumn == column && tempRow == row) && gridWithCell->getCell(tempRow, tempColumn).isAlive()) {
        neighborCount++;
      }
    }
  }
  return neighborCount;
}
