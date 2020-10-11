/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "ClassicMode.h"

using namespace std;

//A game mode whose getNeighborsOfCell class checks for neighbors that are on the opposite side of the grid from where it is, should the cell be on the edge.
class DoughnutMode : public GameMode {
  public:
    //Constructor/Destructor.
    DoughnutMode();
    ~DoughnutMode();

  private:
    //Checks for neighbors that are on the opposite side of the grid from where it is, should the cell be on the edge, in addition to standard neighbors.
    int getNeighborsOfCell(Grid* gridWithCell, int row, int column);
};
