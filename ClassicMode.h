/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "GameMode.h"

using namespace std;

//A game mode whose getNeighborsOfCell class checks for neighbors strictly within the bounds of the grid.
class ClassicMode : public GameMode {
  public:
    //Constructor/Destructor
    ClassicMode();
    ~ClassicMode();

  private:
    //Checks for neighbors strictly within the bounds of the grid.
    int getNeighborsOfCell(Grid* gridWithCell, int row, int column);
};
