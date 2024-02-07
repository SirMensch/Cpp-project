//
// Created by larsl on 2/6/2024.
//

#ifndef SUDOKUSOLVER__STRUCTS_H_
#define SUDOKUSOLVER__STRUCTS_H_

#include <cstdint>
#include <vector>
#include <fstream>

struct Sudoku {
  std::vector<std::vector<uint8_t>> field;

  Sudoku(std::ifstream & iostream){
    uint8_t counter = 0;
    while (counter < 81) {
      char cha = iostream.get();
      if (cha == " " )

    }
  }
};

#endif //SUDOKUSOLVER__STRUCTS_H_
