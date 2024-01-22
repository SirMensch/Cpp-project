cmake_minimum_required(VERSION 3.25)
project(Sudoku)

set(CMAKE_CXX_STANDARD 23)

add_executable(Sudoku main.cpp src/SudokuField.cpp header/SudokuField.h src/SudokuChecker.cpp header/SudokuChecker.h src/SudokuGenerator.cpp header/SudokuGenerator.h)
