#include <iostream>
#include <memory>
#include "Simulator.h"


int main() {

  std::unique_ptr<Simulator> simulator = std::make_unique<Simulator>();



  std::cout << "Hello, World!" << std::endl;
  return 0;
}
