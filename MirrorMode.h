#include "DoughnutMode.h"

using namespace std;

class MirrorMode : public GameMode {
  public:
    MirrorMode();
    ~MirrorMode();

  private:
    int getNeighborsOfCell(Grid* gridWithCell, int row, int column);
};
