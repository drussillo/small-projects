#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"
#include "board.h"

struct Player {
  int shipCount;
  struct Ship ships[5];
  enum Cell board[10][10];
};

void updateBoard(struct Player *player);

void inputShips(struct Player *player);

void randomShips(struct Player *computer);

void inputMove(struct Player *target);

void randomMove(struct Player *target);

bool checkIfLose(struct Player *player);


#endif
