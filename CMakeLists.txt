cmake_minimum_required(VERSION 3.10)
project(TypingTest C)

set(CMAKE_C_STANDARD 99)

add_executable(typing_test
    src/main.c
    src/terminal.c
    src/words.c
    src/wordlist.c
)
