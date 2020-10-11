/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include <iostream>
#include <fstream>

using namespace std;

//Class holding the individual cells
class Cell {
  public:
    //Constructors/Destructors
    Cell();
    Cell(bool isAlive);
    ~Cell();

    //Checks if cell is alive (alive boolean is true)
    bool isAlive();

    //Kills the cell (alive boolean is false)
    void killCell();

    //Creates the cell (alive boolean is true)
    void createCell();

  private:
    //Holds whether or not this cell is alive
    bool alive;
};
