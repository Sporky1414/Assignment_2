#include "ClassicMode.h"

using namespace std;

class DoughnutMode : public GameMode {
  public:
    DoughnutMode();
    ~DoughnutMode();

  private:
    int getNeighborsOfCell(Grid* gridWithCell, int row, int column);
};
