/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "Grid.h"

//Default Constructor: Makes a 5x5 array of alive cells
Grid::Grid() {
  //Sets variables for Grid class
  bool cellAlive = true;
  height = 5;
  width = 5;

  //Creates 2D array of cells
  grid = new Cell* [5];
  for(int i = 0; i < 5; ++i) {
    grid[i] = new Cell[5];
  }

  //Creates a living cell in each index of the array.
  for(int i = 0; i < 5; ++i) {
    for(int j = 0; j < 5; ++j) {
      grid[i][j] = new Cell(cellAlive);
    }
  }
}

//Makes a Grid object based on a file object.
Grid::Grid(FileIO* file) {
  //Reads the height from the file
  string tempString = "";
  tempString = file->readNextLine();

  //Converts the height from string to an int
  stringstream gridMaker(tempString);
  int tempHeight = 0;
  gridMaker >> tempHeight;
  gridMaker.clear();

  //Gets the width from the file on the next line, then converts it from a string to an int.
  tempString = file->readNextLine();
  gridMaker.str(tempString);
  int tempWidth = 0;
  gridMaker >> tempWidth;

  //Creates a 2D array of cells with the height setting the number of rows and width setting the number of columns.
  grid = new Cell* [tempHeight];
  for(int i = 0; i < tempHeight; ++i) {
    grid[i] = new Cell[tempWidth];
  }

  /*
  Reads each line from the grid. Since each cell is instantiated to true, the for loop sets each one based on the file.
  If the file has an X, the cell is alive. If the file has a -, the cell is dead.
  */
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

  //Sets height/width variables
  height = tempHeight;
  width = tempWidth;
}

//Constructor of a grid using a user inputted height/width/population density
Grid::Grid(int tempHeight, int tempWidth, double popDensity) {
  //Creates a new 2D array using the height/width submitted from the users. Cells are initially set to true.
  grid = new Cell* [tempHeight];
  for(int i = 0; i < tempHeight; ++i) {
    grid[i] = new Cell [tempWidth];
  }
  //Seeds a random number generator.
  srand(time(0));

  /*
    For each loop iteration, it takes in a random number from 0-1 (using randomNum()).
    If that number is less than the population density, a living cell is set to the specified point in the loop.
    If that number is greater than the population density, a dead cell is set to the specified point in the loop.
  */
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

  //Sets the height and the width of the cell.
  height = tempHeight;
  width = tempWidth;
}

//Constructor: Copies data from another grid to this one.
Grid::Grid(Grid* oldGrid) {
  //Copies the height/width variables from the old grid.
  height = oldGrid->getHeight();
  width = oldGrid->getWidth();

  //Creates a 2D array of cells. Cells are initially all living.
  grid = new Cell* [height];
  for(int i = 0; i < height; ++i) {
    grid[i] = new Cell[width];
  }

  //Copies whether or not a cell is alive in the old grid to the corresponding cell in the new grid.
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

//Destructor: Deletes the 2D array holding the cells.
Grid::~Grid() {
  for(int i = height - 1; i >= 0; i--) {
    delete[] grid[i];
  }
  delete[] grid;
}

//Returns the cell at the given index of the array.
Cell Grid::getCell(int tempHeight, int tempWidth) {
  return grid[tempHeight][tempWidth];
}

//Gets random num from 0 to 1
double Grid::randomNum() {
  double temp = ((double) rand() / RAND_MAX);
  return temp;
}

/*
  Prints out the grid array as a string. If a cell is alive, an X is used to denote the cell as such.
  If a cell is dead, a - is used to denote the cell as such.
*/
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

//Returns height of the array (number of rows)
int Grid::getHeight() {
  return height;
}

//Returns width of the array (number of columns)
int Grid::getWidth() {
  return width;
}

//Uses the "killCell()" method in the specified cell of the array. Returns that cell's living/deceased status.
bool Grid::killCell(int row, int column) {
  grid[row][column].killCell();
  return grid[row][column].isAlive();
}

//Uses the "createCell()" method in the specified cell of the array. Returns that cell's living/deceased status.
bool Grid::createCell(int row, int column) {
  grid[row][column].createCell();
  return grid[row][column].isAlive();
}

/*
  Sees if all cells in a grid are dead. If so, the method returns true.
  If one cell is found alive, the method returns false without continuing in the loop.
*/
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
