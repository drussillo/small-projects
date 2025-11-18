#include "board.h"

#include <stdio.h>
#include <stdbool.h>

void resetBoard(enum Cell board[BOARD_SIZE][BOARD_SIZE]) {
  for(int i = 0; i < BOARD_SIZE; i++) {
    for(int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = WATER;
    }
  }
}

void printBoard(enum Cell board[BOARD_SIZE][BOARD_SIZE], bool hideShips) {
  puts(COLOR_GREEN"   0 1 2 3 4 5 6 7 8 9");
  for(int i = 0; i < BOARD_SIZE; i++) {
    printf(COLOR_GREEN"%d ", i);
    for(int j = 0; j < BOARD_SIZE; j++) {
      switch(board[i][j]) {
        case WATER:
          printf(COLOR_BLUE"| ");
          break;
        case MISS:
          printf(COLOR_BLUE"|"COLOR_RESET"~");
          break;
        case HIT:
          printf(COLOR_BLUE"|"COLOR_RED"X");
          break;
        case SHIP:
          if(hideShips) {
            printf(COLOR_BLUE"| ");
          } else {
            printf(COLOR_BLUE"|"COLOR_CYAN"=");
          }
          break;
        case SUNKEN:
          printf(COLOR_BLUE"|"COLOR_GRAY"X");
          break;
      }
    }
    printf(COLOR_BLUE"|\n");
  }
}


