#include <stdio.h>
#include <stdbool.h>

#include "utils.h"
#include "player.h"
#include "board.h"

int main() {
  struct Player player;
  struct Player computer;

  resetBoard(player.board);
  inputShips(&player);
  // randomShips(&player);

  resetBoard(computer.board);
  randomShips(&computer);

  bool running = true;
  while(running) {
    // main loop
    updateBoard(&player);
    updateBoard(&computer);
    clearScreen();
    printf(COLOR_YELLOW"\n\nCOMPUTER\n");
    printBoard(computer.board, true);
    printf(COLOR_YELLOW"\n\nYOU\n");
    printBoard(player.board, false);
    inputMove(&computer);
    randomMove(&player);

    if(checkIfLose(&player)) {
      printf("YOU LOSE!");
      getchar();
      running = false;
    }
    if(checkIfLose(&computer)) {
      printf("YOU WIN!");
      getchar();
      running = false;
    }
  }

  printf("Thank you for playing!\n");

  return 0;
}
