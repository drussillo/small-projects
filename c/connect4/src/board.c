#include "board.h"

#include <stdio.h>
#include <stdbool.h>


void initBoard(enum Square board[6][7]) {
  for(int row = 0; row < 6; row++) {
    for(int col = 0; col < 7; col++) {
      board[row][col] = EMPTY;
    }
  }
}


void printBoard(enum Square board[6][7]) {
  for(int row = 0; row < 6; row++) {
    for(int col = 0; col < 7; col++) {
      switch(board[row][col]) {
        case EMPTY:
          printf(COLOR_RESET"| ");
          break;
        case RED:
          printf(COLOR_RESET"|"COLOR_RED"*");
          break;
        case YELLOW:
          printf(COLOR_RESET"|"COLOR_YELLOW"*");
          break;
      }
    }
    puts(COLOR_RESET"|");
  }
  puts(
    "-"COLOR_GREEN"1"COLOR_RESET
    "-"COLOR_GREEN"2"COLOR_RESET
    "-"COLOR_GREEN"3"COLOR_RESET
    "-"COLOR_GREEN"4"COLOR_RESET
    "-"COLOR_GREEN"5"COLOR_RESET
    "-"COLOR_GREEN"6"COLOR_RESET
    "-"COLOR_GREEN"7"COLOR_RESET"-"
  );
}


bool addSquare(enum Square board[6][7], enum Square color, int col) {
  for(int row = 6; row >= 0; row--) {
    if(board[row][col] == EMPTY) {
      board[row][col] = color;
      return true;
    }
  }
  return false;
}


enum Square getWinner(enum Square board[6][7]) {
  // TODO
  for(int row = 0; row < 6; row++) {
    for(int col = 0; col < 7; col++) {
      if(board[row][col] == EMPTY) continue;
      // check horizontal
      for(int connect = 0; connect < 4; connect++) {
        if(col + connect > 6 || board[row][col + connect] != board[row][col]) break;
        if(connect == 3) return board[row][col];
      }
      // check vertical
      for(int connect = 0; connect < 4; connect++) {
        if(row + connect > 5 || board[row + connect][col] != board[row][col]) break;
        if(connect == 3) return board[row][col];
      }
      // check diagonal (right)
      for(int connect = 0; connect < 4; connect++) {
        if(row + connect > 5 || col + connect > 6 || board[row + connect][col + connect] != board[row][col]) break;
        if(connect == 3) return board[row][col];
      }
      // check diagonal (left)
      for(int connect = 0; connect < 4; connect++) {
        if(row + connect > 5 || col - connect < 0 || board[row + connect][col - connect] != board[row][col]) break;
        if(connect == 3) return board[row][col];
      }
    }
  }
  return EMPTY;
}


void clearScreen(void) {
  printf("\033[2J\033[H");
}
