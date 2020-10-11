/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "Grid.h"

using namespace std;

//Base class of type GameMode to determine how many neighbors a cell has (defined by derived classes) and creates a grid from this data.
class GameMode {
  public:
    //Constructor
    GameMode();
    //Creates a new grid based on the number of neighbors each cell has.
    Grid* createNewGridFromOldGrid(Grid* oldGrid);

    //Destructor - virtual to allow for derived class destructors to also be run.
    virtual ~GameMode();

  private:
    //Gets the neighbors of each cell. Differs in implementation in all derived classes, so it is a purely virtual function here as a result.
    virtual int getNeighborsOfCell(Grid* gridWithCell, int row, int column) = 0;
};
