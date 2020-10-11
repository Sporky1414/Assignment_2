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

  private:
    bool alive;
};
