#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void clearLine();
void clearScreen();
void disableRawMode();
void enableRawMode();
void moveCursorTo(int row, int col);

#endif // TERMINAL_H
