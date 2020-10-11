/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include <iostream>
#include <fstream>
#include "FileIO.h"
#include "Cell.h"

using namespace std;

//Class that holds a 2D array of cells
class Grid {
  public:
    //Constructors/Destructors
    Grid();
    Grid(FileIO* file);
    Grid(int height, int width, double popDensity);
    Grid(Grid* oldGrid);
    ~Grid();

    //Returns the cell at a position
    Cell getCell(int height, int width);

    //Kills/Creates the cell at a position
    bool killCell(int row, int column);
    bool createCell(int row, int column);

    //Returns if all cells in the grid are dead
    bool isEmpty();

    //Prints the grid to a string
    string gridToString();

    //Returns the height/width of the grid array.
    int getHeight();
    int getWidth();

  private:
    //2D array holding cell data
    Cell **grid;

    //Height/Width of the grid
    int height;
    int width;

    //Returns a random number from 0-1.
    double randomNum();
};
