#include "words.h"
#include "wordlist.h"
#include <ctype.h>
#include <sys/ioctl.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

void printWordsWithColor(const char **words, int numWords, const char *input, int inputLength)
{
	struct winsize w;
	ioctl(fileno(stdout), TIOCGWINSZ, &w);
	int termWidth = w.ws_col;
	int termHeight = w.ws_row;

	int inputIndex = 0;
	int currentLine = 0;
	int currentColumn = 0;

	for (int i = 0; i < numWords; i++)
	{
		int wordLength = strlen(words[i]);
		if (currentColumn + wordLength >= termWidth)
		{
			currentColumn = 0;
			currentLine++;
			printf("\n");
		}

		if (currentColumn == 0)
		{
			int lineLength = 0;
			for (int j = i; j < numWords && lineLength + strlen(words[j]) < termWidth; j++)
			{
				lineLength += strlen(words[j]) + 1;
			}
			int padSize = (termWidth - lineLength) / 2;
			printf("%*s", padSize, "");
			currentColumn = padSize;
		}

		for (int j = 0; j < wordLength; j++)
		{
			if (inputIndex < inputLength)
			{
				if (words[i][j] == input[inputIndex])
				{
					printf("\033[1;37m%c\033[0m", words[i][j]); // white
				}
				else
				{
					printf("\033[1;31m%c\033[0m", words[i][j]); // red
				}
				inputIndex++;
			}
			else
			{
				printf("\033[1;30m%c\033[0m", words[i][j]); // gray
			}
			currentColumn++;
		}

		if (i < numWords - 1)
		{
			if (inputIndex < inputLength)
			{
				if (input[inputIndex] == ' ')
				{
					printf("\033[1;37m \033[0m"); // white
				}
				else
				{
					printf("\033[1;31m \033[0m"); // red
				}
				inputIndex++;
			}
			else
			{
				printf("\033[1;30m \033[0m"); // gray
			}
			currentColumn++;
		}
	}
	printf("\n");
}

void shuffleWords(const char **words, int numWords, const char **selectedWords)
{
	int used[WORD_COUNT] = {0};
	srand(time(NULL));
	for (int i = 0; i < numWords; i++)
	{
		int index;
		do
		{
			index = rand() % WORD_COUNT;
		} while (used[index]);
		used[index] = 1;
		selectedWords[i] = words[index];
	}
}

int getNumberOfWords()
{
	char input[10];
	int index = 0;
	char c;
	while (1)
	{
		c = getchar();
		if (c == '\r' || c == '\n')
		{
			input[index] = '\0';
			break;
		}
		else if (c == 127 || c == '\b')
		{
			if (index > 0)
			{
				index--;
				input[index] = '\0';
				printf("\b \b");
			}
		}
		else if (isdigit(c))
		{
			if (index < 9)
			{
				input[index] = c;
				index++;
				input[index] = '\0';
				printf("%c", c);
			}
		}
	}
	return atoi(input);
}

void runTypingTest(int numWords)
{
	const char *selectedWords[numWords];
	shuffleWords(words, numWords, selectedWords);

	char input[MAX_INPUT_LENGTH] = {0};
	int inputIndex = 0;
	time_t start = time(NULL);

	struct winsize w;
	ioctl(fileno(stdin), TIOCGWINSZ, &w);
	int termHeight = w.ws_row;

	int lineCount = 1;
	int currentLineWidth = 0;
	for (int i = 0; i < numWords; i++)
	{
		int wordLength = strlen(selectedWords[i]);
		if (currentLineWidth + wordLength >= w.ws_col)
		{
			lineCount++;
			currentLineWidth = 0;
		}
		currentLineWidth += wordLength + 1;
	}

	int verticalPadding = (termHeight - lineCount) / 2;
	int isRunning = 1;

	while (isRunning)
	{
		clearScreen();
		moveCursorTo(verticalPadding, 0);
		printWordsWithColor(selectedWords, numWords, input, inputIndex);
		char c = getchar();
		if (c == 27)
			isRunning = 0;
		else if (c == '\r' || c == '\n')
			isRunning = 0;

		if (c == 127 || c == '\b')
		{
			if (inputIndex > 0)
			{
				inputIndex--;
				input[inputIndex] = '\0';
			}
		}
		else if (c == ' ')
		{
			input[inputIndex] = c;
			inputIndex++;
			input[inputIndex] = '\0';
		}
		else if (isprint(c))
		{
			if (inputIndex < MAX_INPUT_LENGTH)
			{
				input[inputIndex] = c;
				inputIndex++;
				input[inputIndex] = '\0';
			}
		}
	}

	time_t end = time(NULL);
	double elapsed = difftime(end, start);
	int correctChars = 0;
	int totalChars = 0;

	for (int i = 0; i < numWords; i++)
	{
		int wordLength = strlen(selectedWords[i]);
		for (int j = 0; j < wordLength; j++)
		{
			if (input[totalChars] == selectedWords[i][j])
			{
				correctChars++;
			}
			totalChars++;
		}
		totalChars++;
	}

	double cpm = (double)correctChars / elapsed * 60;
	double wpm = (correctChars / 5.0) / (elapsed / 60.0);
	double accuracy = (correctChars / (double)totalChars) * 100;

	printf("\nStatistics:\n");
	printf("Time taken: ");
	printf("\x1b[34m%.2f\x1b[0m seconds\n", elapsed);
	printf("CPM (Characters per minute): ");
	printf("\x1b[34m%.2f\x1b[0m\n", cpm);
	printf("WPM (Words per minute): ");
	printf("\x1b[34m%.2f\x1b[0m\n", wpm);
	printf("Accuracy: ");
	printf("\x1b[34m%.2f%%\x1b[0m\n", accuracy);
}
