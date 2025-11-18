#ifndef SHIP_H
#define SHIP_H

#include <stdbool.h>


enum ShipType {
  DESTROYER,
  SUBMARINE,
  CRUISER,
  BATTLESHIP,
  CARRIER
};

enum Direction {
  HORIZONTAL,
  VERTICAL
};


struct Ship {
  int row;
  int col;
  int hits;
  enum ShipType type;
  enum Direction dir;
};


int getShipSize(enum ShipType type);

char *getShipName(enum ShipType type);

bool isOn(struct Ship ship, int row, int col);

// If hit, applies effect to that ship and returns true. If not, returns false.
bool hit(struct Ship targetShips[5], int row, int col);

bool overlaps(struct Ship ship1, struct Ship ship2);

bool hasSunk(struct Ship ship);


#endif
