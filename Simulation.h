#include "MirrorMode.h"

using namespace std;

class Simulation {
  public:
    Simulation();
    ~Simulation();

    void run();
  private:
    Grid* mainGrid;
    Grid* prevGrid;
    FileIO* fileHandler;
    GameMode* mode;

    ClassicMode classic;
    DoughnutMode doughnut;
    MirrorMode mirror;

    void setupSimulation();
    void getGridFromUser();
    void setupFile();
    void gameModeSetup();

    bool fileBeingInputted;
    bool fileBeingOutputted;
    bool pauseBetweenGenerations;

    string userResponse;
    int heightFromUser;
    int widthFromUser;
    double popDensityFromUser;
    int countOfStability;
};
