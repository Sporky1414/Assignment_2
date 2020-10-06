#include <iostream>
#include <fstream>

using namespace std;

class Cell {
  public:
    Cell();
    Cell(bool isAlive);
    ~Cell();

    bool isAlive();
    void killCell();
    void createCell();
    void setNeighbors(int newNeighborsAmt);
    int getNeighbors();

  private:
    bool alive;
    int neighbors;
};
