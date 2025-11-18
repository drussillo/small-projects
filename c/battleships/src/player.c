#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ship.h"
#include "utils.h"


void updateBoard(struct Player *player) {
  for(int i = 0; i < player->shipCount; i++) {
    if(player->ships[i].dir == HORIZONTAL) {
      for(int j = player->ships[i].col; j < player->ships[i].col + getShipSize(player->ships[i].type); j++) {
        if(player->board[player->ships[i].row][j] == HIT && hasSunk(player->ships[i])) {
          player->board[player->ships[i].row][j] = SUNKEN;
        }
        if(player->board[player->ships[i].row][j] != HIT && player->board[player->ships[i].row][j] != SUNKEN) {
          player->board[player->ships[i].row][j] = SHIP;
        }
      }
    } else {
      for(int j = player->ships[i].row; j < player->ships[i].row + getShipSize(player->ships[i].type); j++) {
        if(player->board[j][player->ships[i].col] == HIT && hasSunk(player->ships[i])) {
          player->board[j][player->ships[i].col] = SUNKEN;
        }
        if(player->board[j][player->ships[i].col] != HIT && player->board[j][player->ships[i].col] != SUNKEN) {
          player->board[j][player->ships[i].col] = SHIP;
        }
      }
    }
  }
}


void inputShips(struct Player *player) {
  char directionInput;
  int rowInput;
  int colInput;
  player->shipCount = 0;

  for(int currentShip = 0; currentShip < 5; currentShip++) {
    clearScreen();
    printBoard(player->board, false);
    printf(COLOR_YELLOW"Enter %s direction (h/v), row (0-9), and column (0-9): "COLOR_RESET, getShipName(4 - currentShip));
    scanf("%c %d %d", &directionInput, &rowInput, &colInput);
    flushInput(); 

    // TODO add validity check

    player->ships[currentShip].row = rowInput;
    player->ships[currentShip].col = colInput;
    player->ships[currentShip].hits = 0;
    player->ships[currentShip].type = 4 - currentShip;
    if(directionInput == 'h') {
      player->ships[currentShip].dir = HORIZONTAL;
    } else {
      player->ships[currentShip].dir = VERTICAL;
    }
    player->shipCount++;
  }
}


void randomShips(struct Player *computer) {
  srand(time(NULL));
  computer->shipCount = 0;

  for(int currentShip = 0; currentShip < 5; currentShip++) {

    int randomDir;
    int randomRow;
    int randomCol;


    randomDir = rand() % 2;
    randomRow = rand() % BOARD_SIZE;
    randomCol = rand() % BOARD_SIZE;

    bool valid = false;
    while(!valid) {
      randomDir = rand() % 2;
      if(randomDir == HORIZONTAL) {
        randomRow = rand() % BOARD_SIZE;
        randomCol = rand() % (BOARD_SIZE - getShipSize(currentShip));
      } else {
        randomRow = rand() % (BOARD_SIZE - getShipSize(currentShip));
        randomCol = rand() % BOARD_SIZE;
      }

      computer->ships[currentShip].row = randomRow;
      computer->ships[currentShip].col = randomCol;
      computer->ships[currentShip].hits = 0;
      computer->ships[currentShip].type = currentShip;
      computer->ships[currentShip].dir = randomDir;

      valid = true;
      for(int i = 0; i < currentShip; i++) {
        if(overlaps(computer->ships[i], computer->ships[currentShip])) {
          valid = false;
          break;
        }
      }
    }

    computer->shipCount++;
  }
}


void inputMove(struct Player *target) {
  int attackRow;
  int attackCol;

  printf(COLOR_YELLOW"Choose which enemy cell to attack (0-9 0-9): "COLOR_RESET);
  scanf("%d %d", &attackRow, &attackCol);
  flushInput();
  // TODO check input validity

  if(hit(target->ships, attackRow, attackCol)) {
    target->board[attackRow][attackCol] = HIT;
  } else {
    target->board[attackRow][attackCol] = MISS;
  }
}


void randomMove(struct Player *target) {

  int attackRow = rand() % BOARD_SIZE;
  int attackCol = rand() % BOARD_SIZE;

  // TODO check input validity

  if(hit(target->ships, attackRow, attackCol)) {
    target->board[attackRow][attackCol] = HIT;
  } else {
    target->board[attackRow][attackCol] = MISS;
  }
}


bool checkIfLose(struct Player *player) {
  bool lose = true;
  for(int i = 0; i < 5; i++) {
    if(!hasSunk(player->ships[i])) {
      lose = false;
    }
  }
  return lose;
}


