#include "Grid.h"

Grid::Grid() {
  bool cellAlive = true;
  height = 5;
  width = 5;
  grid = new Cell* [5];
  for(int i = 0; i < 5; ++i) {
    grid[i] = new Cell[5];
  }

  for(int i = 0; i < 5; ++i) {
    for(int j = 0; j < 5; ++j) {
      grid[i][j] = new Cell(cellAlive);
    }
  }
}

Grid::Grid(FileIO* file) {
  string tempString = "";
  tempString = file->readNextLine();
  stringstream gridMaker(tempString);
  int tempHeight = 0;
  gridMaker >> tempHeight;
  gridMaker.clear();

  tempString = file->readNextLine();
  gridMaker.str(tempString);
  int tempWidth = 0;
  gridMaker >> tempWidth;

  grid = new Cell* [tempHeight];
  for(int i = 0; i < tempHeight; ++i) {
    grid[i] = new Cell[tempWidth];
  }

  tempString = "";
  for(int i = 0; i < tempHeight; ++i) {
    tempString = file->readNextLine();
    for(int j = 0; j < tempString.length(); ++j) {
      if(tempString[j] == '-') {
        grid[i][j].killCell();
      } else {
        grid[i][j].createCell();
      }
    }
  }
  height = tempHeight;
  width = tempWidth;
}

Grid::Grid(int tempHeight, int tempWidth, double popDensity) {
  grid = new Cell* [tempHeight];
  for(int i = 0; i < tempHeight; ++i) {
    grid[i] = new Cell [tempWidth];
  }
  srand(time(0));
  for(int i = 0; i < tempHeight; ++i) {
    for(int j = 0; j < tempWidth; ++j) {
      double tempNum = randomNum();
      if(tempNum <= popDensity) {
        grid[i][j].createCell();
      } else {
        grid[i][j].killCell();
      }
    }
  }
  height = tempHeight;
  width = tempWidth;
}

Grid::Grid(Grid* oldGrid) {
  height = oldGrid->getHeight();
  width = oldGrid->getWidth();
  grid = new Cell* [height];
  for(int i = 0; i < height; ++i) {
    grid[i] = new Cell[width];
  }
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      if(oldGrid->getCell(i, j).isAlive()) {
        grid[i][j].createCell();
      } else {
        grid[i][j].killCell();
      }
    }
  }
}

Grid::~Grid() {
  for(int i = height - 1; i >= 0; i--) {
    delete[] grid[i];
  }
  delete[] grid;
}

Cell Grid::getCell(int tempHeight, int tempWidth) {
  return grid[tempHeight][tempWidth];
}

//Gets random num from 0 to 1
double Grid::randomNum() {
  double temp = ((double) rand() / RAND_MAX);
  return temp;
}

string Grid::gridToString() {
  string returnString = "";
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      if(grid[i][j].isAlive()) {
        returnString = returnString + 'X';
      } else {
        returnString = returnString + '-';
      }
    }
    returnString = returnString + '\n';
  }
  return returnString;
}

int Grid::getHeight() {
  return height;
}

int Grid::getWidth() {
  return width;
}

bool Grid::killCell(int row, int column) {
  grid[row][column].killCell();
  return grid[row][column].isAlive();
}

bool Grid::createCell(int row, int column) {
  grid[row][column].createCell();
  return grid[row][column].isAlive();
}

bool Grid::isEmpty() {
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      if(grid[i][j].isAlive()) {
        return false;
      }
    }
  }
  return true;
}
