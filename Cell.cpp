/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 2
*/

#include "Cell.h"

//Defaults cell to true
Cell::Cell() {
  alive = true;
}

//Sets the alive boolean to the parameter passed through
Cell::Cell(bool isAlive) {
  if(isAlive) {
    alive = true;
  } else {
    alive = false;
  }
}

//Nothing needs to be clearned out, so destructor remains empty.
Cell::~Cell() {}

//Returns the alive boolean
bool Cell::isAlive() {
  return alive;
}

//Sets the alive boolean to false
void Cell::killCell() {
  if(alive) {
    alive = false;
  }
}

//Sets the alive boolean to true
void Cell::createCell() {
  if(!alive) {
    alive = true;
  }
}
