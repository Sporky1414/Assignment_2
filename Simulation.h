/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "MirrorMode.h"

using namespace std;

//The class that runs the Game of Life simulation
class Simulation {
  public:
    //Constructor/Destructor
    Simulation();
    ~Simulation();

    //Method to run the simulation
    void run();
  private:
    //Grid objects holding the main grid and the previous version of the grid in the simulation
    Grid* mainGrid;
    Grid* prevGrid;

    //FileIO object to handle file input/output.
    FileIO* fileHandler;

    //GameMode pointer points to the correct game mode to get a cell's neighbors and create the new cell based on those neighbors
    GameMode* mode;

    //Each mode needs to be defined globally due to scope issues, even if they will not be in use.
    ClassicMode classic;
    DoughnutMode doughnut;
    MirrorMode mirror;

    //Prepares the simulation
    void setupSimulation();

    //Creates the mainGrid using user-provided information.
    void getGridFromUser();

    //Sets up the fileHandler
    void setupFile();

    //Sets up the mode pointer
    void gameModeSetup();

    //Says if a file is being inputted and if one is being outputted.
    bool fileBeingInputted;
    bool fileBeingOutputted;

    //Determines if there will be a pause between generations.
    bool pauseBetweenGenerations;

    //Inputs from the user.
    string userResponse;
    int heightFromUser;
    int widthFromUser;
    double popDensityFromUser;
};
