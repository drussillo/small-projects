#ifndef BOARD_H
#define BOARD_H

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_GRAY    "\033[90m"

#define BOARD_SIZE 10

#include <stdbool.h>

enum Cell {
  WATER,
  MISS,
  SHIP,
  HIT,
  SUNKEN
};


void resetBoard(enum Cell board[BOARD_SIZE][BOARD_SIZE]);

void printBoard(enum Cell board[BOARD_SIZE][BOARD_SIZE], bool hideShips);


#endif
