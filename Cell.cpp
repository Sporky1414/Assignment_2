#include "Cell.h"

Cell::Cell() {
  alive = true;
}

Cell::Cell(bool isAlive) {
  if(isAlive) {
    alive = true;
  } else {
    alive = false;
  }
}

Cell::~Cell() {

}

bool Cell::isAlive() {
  return alive;
}

void Cell::killCell() {
  if(alive) {
    alive = false;
  }
}

void Cell::createCell() {
  if(!alive) {
    alive = true;
  }
}
