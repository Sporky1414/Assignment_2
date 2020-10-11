#include "ClassicMode.h"

ClassicMode::ClassicMode() {}

ClassicMode::~ClassicMode() {}

int ClassicMode::getNeighborsOfCell(Grid* gridWithCell, int row, int column) {
  int neighborCount = 0;
  int minBoundHeight = 0;
  int minBoundWidth = 0;
  int maxBoundHeight = gridWithCell->getHeight() - 1;
  int maxBoundWidth = gridWithCell->getWidth() - 1;
  if(row != 0) {
    minBoundHeight = row - 1;
  }
  if(row != maxBoundHeight) {
    maxBoundHeight = row + 1;
  }
  if(column != 0) {
    minBoundWidth = column - 1;
  }
  if(column != maxBoundWidth) {
    maxBoundWidth = column + 1;
  }
  for(int i = minBoundHeight; i <= maxBoundHeight; ++i) {
    for(int j = minBoundWidth; j <= maxBoundWidth; ++j) {
      if(!(i == row && j == column) && gridWithCell->getCell(i, j).isAlive()) {
        neighborCount++;
      }
    }
  }
  return neighborCount;
}
