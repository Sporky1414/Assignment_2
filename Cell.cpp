#include "Cell.h"

Cell::Cell() {
  alive = true;
  neighbors = 0;
}

Cell::Cell(bool isAlive) {
  alive = isAlive;
  neighbors = 0;
}

Cell::~Cell() {

}

bool Cell:isAlive() {
  return alive;
}

void Cell::killCell() {
  if(alive) {
    alive = false;
  } else {
    cout << "No Change, Since Cell is Dead Already" << endl;
  }
}

void Cell::createCell() {
  if(!alive) {
    alive = true;
  } else {
    cout << "No Change, Since Cell is Alive Already" << endl;
  }
}

void setNeighbors(int newNeighborsAmt) {
  if(newNeighborsAmt < 0) {
    cout << "Invalid Neighbor Amount Passed. No change made to this cell." << endl;
  } else {
    neighbors = newNeighborsAmt;
  }
}

int getNeighbors() {
  return neighbors;
}
