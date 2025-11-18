#include "utils.h"

#include <stdio.h>

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


void clearScreen() {
  printf("\033[2J\033[H");
}
