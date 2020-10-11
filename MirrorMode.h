/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "DoughnutMode.h"

using namespace std;

//A game mode whose getNeighborsOfCell class checks for neighbors that are reflections near where it is, should the cell be on the edge.
class MirrorMode : public GameMode {
  public:
    //Constructor/Destructor
    MirrorMode();
    ~MirrorMode();

  private:
    //Checks for neighbors that are reflections near where it is, should the cell be on the edge, in addition to standard neighbors.
    int getNeighborsOfCell(Grid* gridWithCell, int row, int column);
};
