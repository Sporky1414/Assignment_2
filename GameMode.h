#include "Grid.h"

using namespace std;

class GameMode {
  public:
    GameMode();
    Grid* createNewGridFromOldGrid(Grid* oldGrid);
    virtual ~GameMode();

  private:
    virtual int getNeighborsOfCell(Grid* gridWithCell, int row, int column) = 0;
};
