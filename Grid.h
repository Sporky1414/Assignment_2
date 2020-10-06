#include <iostream>
#include <fstream>

using namespace std;

class Grid {
  public:
    Grid();
    Grid(FileIO file);
    Grid(int height, int width, double popDensity);
    ~Grid();

    Cell getCell(int height, int width);
    string gridToString();

  private:
    Cell[][] grid*;

    double randomNum();
};
