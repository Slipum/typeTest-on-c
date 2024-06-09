#include "common.h"
#include "terminal.h"
#include "words.h"

int main()
{
	enableRawMode();
	int isRunning = 1;

	while (isRunning)
	{
		clearScreen();
		printf("Enter the number of words you want to type: ");
		int numWords = getNumberOfWords();

		if (numWords > WORD_COUNT)
		{
			printf("Number of words exceeds available words. Setting to %d.\n", WORD_COUNT);
			numWords = WORD_COUNT;
		}

		clearScreen();
		int repeatTest = 1;

		while (repeatTest)
		{
			runTypingTest(numWords);

			printf("\nPress Enter to try again, 'c' to change number of words, or ESC to exit.\n");
			char c = getchar();
			if (c == 27)
			{
				isRunning = 0;
				repeatTest = 0;
			}
			else if (c == 'c' || c == 'C')
			{
				repeatTest = 0;
			}
			clearScreen();
		}
	}

	disableRawMode();
	return 0;
}
