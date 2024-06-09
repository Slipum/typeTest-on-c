#include "terminal.h"

struct termios orig_termios;

void clearLine()
{
	printf("\033[K");
}

void clearScreen()
{
	printf("\033[H\033[J");
}

void disableRawMode()
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode()
{
	struct termios raw;
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);
	raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void moveCursorTo(int row, int col)
{
	printf("\033[%d;%dH", row, col);
}
