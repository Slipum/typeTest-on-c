# Typing Speed Test Application

This is a console-based typing speed test application written in C. It measures your typing speed in characters per minute (CPM) and words per minute (WPM) and calculates your accuracy.

## Features

- Generates a random sequence of words for the typing test
- Measures typing speed in characters per minute (CPM) and words per minute (WPM)
- Calculates typing accuracy
- Highlights correct, incorrect, and remaining characters in different colors
- Adjustable number of words for the test
- Centered text display for better readability
- Handles user input, including backspaces and spaces

## Updated Project Structure

```
typing_test/
├── CMakeLists.txt
├── src/
│   ├── main.c
│   ├── terminal.c
│   ├── terminal.h
│   ├── words.c
│   ├── words.h
│   ├── common.h
│   ├── wordlist.c
│   └── wordlist.h
```

## Installation

1. Clone the repository:

```bash
git clone https://github.com/yourusername/typing-speed-test.git
```

2. Navigate to the project directory:

```bash
cd typing-speed-test
```

3. Create a `build` directory and navigate to it:

```bash
mkdir build
cd build
```

4. Compile the program using CMake:

```bash
cmake ..
make
```

## Usage

1. Run the compiled program:

```bash
./typing_test
```

2. Enter the number of words you want to type.
3. Start typing the displayed words. Make sure to include spaces between words.
4. The test ends when you press the Enter key.
5. View your typing statistics, including time taken, CPM, WPM, and accuracy.

## Code Overview

### Main Functions

- `clearLine()`: Clears the current line in the console.
- `clearScreen()`: Clears the entire console screen.
- `disableRawMode()`: Restores the terminal to its original state.
- `enableRawMode()`: Sets the terminal to raw mode to capture input directly.
- `moveCursorTo(int row, int col)`: Moves the cursor to a specific position on the screen.
- `printWordsWithColor(const char **words, int numWords, const char *input, int inputLength)`: Prints the words for the typing test with colors indicating correct, incorrect, and remaining characters.
- `shuffleWords(const char **words, int numWords, const char **selectedWords)`: Randomly selects words for the typing test.
- `getNumberOfWords()`: Prompts the user to enter the number of words for the test.
- `runTypingTest(int numWords)`: Runs the typing test and calculates the results.

### How It Works

1. **Enable Raw Mode**: The terminal is set to raw mode to handle user input directly.
2. **Word Selection**: A random selection of words is generated based on the user's input for the number of words.
3. **Typing Test**: The selected words are displayed, and the user types them. Correct and incorrect characters are highlighted.
4. **Results Calculation**: Once the user completes the test by pressing Enter, the time taken, CPM, WPM, and accuracy are calculated and displayed.
5. **Repeat or Exit**: The user can choose to repeat the test, change the number of words, or exit the program.

## Example

```bash
Enter the number of words you want to type: 10

test application random words calculate performance
```

The user starts typing the displayed words, and the program highlights the correct, incorrect, and remaining characters in real-time.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request or open an issue on GitHub.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
