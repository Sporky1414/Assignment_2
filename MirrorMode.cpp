#include "MirrorMode.h"

MirrorMode::MirrorMode() {}

MirrorMode::~MirrorMode() {}

int MirrorMode::getNeighborsOfCell(Grid* gridWithCell, int row, int column) {
  int neighborCount = 0;
  int minBoundHeight = 0;
  int minBoundWidth = 0;
  int maxBoundHeight = gridWithCell->getHeight() - 1;
  int maxBoundWidth = gridWithCell->getWidth() - 1;
  bool onEdge = false;
  bool corner = false;

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

  if(row == 0 || column == 0 || row == gridWithCell->getHeight() - 1 || column == gridWithCell->getWidth() - 1) {
    onEdge = true;
    if((row == 0 && column == 0) || (row == 0 && column == gridWithCell->getWidth() - 1) || (row == gridWithCell->getHeight() - 1 && column == 0) || (row == gridWithCell->getHeight() - 1 && column == gridWithCell->getWidth() - 1)) {
      corner = true;
    }
  }
  for(int i = minBoundHeight; i <= maxBoundHeight; ++i) {
    for(int j = minBoundWidth; j <= maxBoundWidth; ++j) {
      if(gridWithCell->getCell(i, j).isAlive()) {
        //normal
        if(!(i == row && j == column)) {
          neighborCount++;
        } else if (onEdge && !corner){
          neighborCount++;
          continue;
        } else if(corner) {
          neighborCount += 3;
          continue;
        }
        //reflection
        if(onEdge && !(corner && i == row && j == column)) {
          if ((i == 0 || i == gridWithCell->getHeight() - 1) && i == row) {
            neighborCount++;
          } else if ((j == 0 || j == gridWithCell->getWidth() - 1) && j == column) {
            neighborCount++;
          }
        }
      }
    }
  }
  return neighborCount;
}
