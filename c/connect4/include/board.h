#ifndef BOARD_H
#define BOARD_H

#define COLOR_RED    "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_RESET  "\x1b[0m"

#include <stdbool.h>

enum Square {
  EMPTY,
  RED,
  YELLOW
};


void initBoard(enum Square board[6][7]);

void printBoard(enum Square board[6][7]);

bool addSquare(enum Square board[6][7], enum Square color, int col);

enum Square getWinner(enum Square board[6][7]);

void clearScreen(void);


#endif
