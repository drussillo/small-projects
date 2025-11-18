#include "ship.h"


int getShipSize(enum ShipType type) {
  switch(type) {
    case DESTROYER:
      return 2;
      break;
    case SUBMARINE:
      return 3;
      break;
    case CRUISER:
      return 3;
      break;
    case BATTLESHIP:
      return 4;
      break;
    case CARRIER:
      return 5;
      break;
  }
}

char *getShipName(enum ShipType type) {
  switch(type) {
    case DESTROYER:
      return "Destroyer (2)";
      break;
    case SUBMARINE:
      return "Submarine (3)";
      break;
    case CRUISER:
      return "Cruiser (3)";
      break;
    case BATTLESHIP:
      return "Battleship (4)";
      break;
    case CARRIER:
      return "Carrier (5)";
      break;
  }
}

bool isOn(struct Ship ship, int row, int col) {
  if(ship.dir == HORIZONTAL) {
    return row == ship.row && col >= ship.col && col <= ship.col + getShipSize(ship.type) - 1;
  } else {
    return col == ship.col && row >= ship.row && row <= ship.row + getShipSize(ship.type) - 1;
  }
}

bool hit(struct Ship targetShips[5], int row, int col) {
  for(int i = 0; i < 5; i++) {
    if(isOn(targetShips[i], row, col)) {
      targetShips[i].hits++;
      return true;
    }
  }
  return false;
}

bool overlaps(struct Ship ship1, struct Ship ship2) {
  if(ship1.dir == HORIZONTAL) {
    for(int i = ship1.col; i < ship1.col + getShipSize(ship1.type); i++) {
      if(isOn(ship2, ship1.row, i)) {
        return true;
      }
    }
  } else {
    for(int i = ship1.row; i < ship1.row + getShipSize(ship1.type); i++) {
      if(isOn(ship2, i, ship1.col)) {
        return true;
      }
    }
  }
  return false;
}


bool hasSunk(struct Ship ship) {
  return ship.hits >= getShipSize(ship.type);
}



