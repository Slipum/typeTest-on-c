#ifndef WORDS_H
#define WORDS_H

#include "common.h"

void printWordsWithColor(const char **words, int numWords, const char *input, int inputLength);
void shuffleWords(const char **words, int numWords, const char **selectedWords);
int getNumberOfWords();
void runTypingTest(int numWords);

#endif // WORDS_H
