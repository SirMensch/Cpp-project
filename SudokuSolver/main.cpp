#include <iostream>
#include <fstream>
#include <sstream>

int main() {
  std::ifstream file("SudokuDummy.txt");
  int x;
  x = file.get();
  std::cout << x;
  std::ostringstream contentStream;
  contentStream << file.rdbuf();
  std::string fileContent = contentStream.str();

  return 0;
}
