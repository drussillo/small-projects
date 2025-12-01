#include <stdio.h>
#include <stdbool.h>

#include "board.h"


int main() {
  enum Square board[6][7];
  initBoard(board);

  enum Square currentPlayer = RED;
  int colInput;

  while(true) {
    // print
    clearScreen();
    puts("\n\n\n\n");
    printBoard(board);

    // check if won
    if(getWinner(board) != EMPTY) {
      if(currentPlayer == RED) printf(COLOR_RED"Red"COLOR_RESET);
      else printf(COLOR_YELLOW"Yellow"COLOR_RESET);
      puts(" WON!");
      break;
    }

    // switch players
    if(currentPlayer == RED) currentPlayer = YELLOW;
    else currentPlayer = RED;

    // make move
    do {
      clearScreen();
      puts("\n\n\n\n");
      printBoard(board);

      puts("\n\n\n\n");
      printf("Player ");
      if(currentPlayer == RED) printf(COLOR_RED"Red"COLOR_RESET);
      else printf(COLOR_YELLOW"Yellow"COLOR_RESET);
      printf(", enter column (1-7): ");
      scanf("%d", &colInput);
    } while(colInput < 1 || colInput > 7 || !addSquare(board, currentPlayer, colInput-1));
  }

  return 0;
}
