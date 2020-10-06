#include "Grid.h"

Grid::Grid() {
  cout << "Creating 5x5 array with every other cell filled." << endl;
  bool cellAlive = true;
  grid* = new Cell[5][5];
  for(int i = 0; i < 5; ++i) {
    for(int j = 0; j < 5; ++j) {
      grid[i][j] = new Cell(cellAlive);
      if(cellAlive) {
        cellAlive = false;
      } else {
        cellAlive = true;
      }
    }
  }
}

Grid::Grid(FileIO file) {
  int height = file.readNextLine();
  int width = file.readNextLine();
  grid* = new Cell[height][width];
  string tempString = "";
  for(int i = 0; i < height; ++i) {
    tempString = file.readNextLine();
    for(int j = 0; j < tempString.length(); ++j) {
      if(tempString[j] == '-') {
        grid[i][j] = new Cell(false);
      } else {
        grid[i][j] = new Cell(true);
      }
    }
  }
}

Grid::Grid(int height, int width, double popDensity) {
  grid* = new Cell[height][width];
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      if(randomNum() <= popDensity) {
        grid[i][j] = new Cell(true);
      } else {
        grid[i][j] = new Cell(false);
      }
    }
  }
}

Grid::~Grid() {
  int tempWidth = sizeOf(grid[0])/sizeOf(grid[0][0]);
  int tempHeight = sizeOf(grid)/sizeOf(grid[0]);
  for(int i = 0; i < tempHeight; ++i) {
    for(int j = 0; j < tempWidth; ++j) {
      delete grid[i][j];
    }
  }
  delete grid;
}

Cell getCell(int height, int width) {
  return grid[height][width];
}

//Gets random num from 0 to 1
double Grid::randomNum() {
  double temp = ((double) rand() / RAND_MAX);
  return temp;
}

string Grid::gridToString() {
  int tempWidth = sizeOf(grid[0])/sizeOf(grid[0][0]);
  int tempHeight = sizeOf(grid)/sizeOf(grid[0]);
  string returnString = tempWidth + "\n" + tempHeight + "\n";
  for(int i = 0; i < tempHeight; ++i) {
    for(int j = 0; j < tempWidth; ++j) {
      if(grid[i][j].isAlive()) {
        returnString = returnString + "X";
      } else {
        returnString = returnString + "-";
      }
    }
    returnString = returnString + "\n";
  }
  return returnString;
}
