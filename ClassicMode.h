#include "GameMode.h"

using namespace std;

class ClassicMode : public GameMode {
  public:
    ClassicMode();
    ~ClassicMode();

  private:
    int getNeighborsOfCell(Grid* gridWithCell, int row, int column);
};
