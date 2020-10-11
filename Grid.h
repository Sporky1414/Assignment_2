#include <iostream>
#include <fstream>
#include "FileIO.h"
#include "Cell.h"

using namespace std;

class Grid {
  public:
    Grid();
    Grid(FileIO* file);
    Grid(int height, int width, double popDensity);
    Grid(Grid* oldGrid);
    ~Grid();

    Cell getCell(int height, int width);
    string gridToString();
    int getHeight();
    int getWidth();
    bool killCell(int row, int column);
    bool createCell(int row, int column);
    bool isEmpty();

  private:
    Cell **grid;

    int height;
    int width;

    double randomNum();
};
