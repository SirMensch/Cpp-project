//
// Created by Lars on 6/27/2023.
// This class defines the board of the Sudoku
#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>

#ifndef SUDOKU_SUDOKUFIELD_H
#define SUDOKU_SUDOKUFIELD_H

#define SUDOKU_SIZE 9

class SudokuField {
private:
    int8_t field[SUDOKU_SIZE][SUDOKU_SIZE]{};
    bool finished = false;
public:
    bool GetStatus();
    void SetFinished();
    void Print();
};

#endif //SUDOKU_SUDOKUFIELD_H
