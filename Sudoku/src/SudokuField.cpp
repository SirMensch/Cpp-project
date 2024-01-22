//
// Created by larsl on 6/27/2023.
//

#include "../header/SudokuField.h"

bool SudokuField::GetStatus() {
    return finished;
}

void SudokuField::Print() {
    for (auto & i : field) {
        for (int8_t j : i) {
            std::cout << (int) j;
            std::cout << " ";
        }
    std::cout << "\n";
    }
}
