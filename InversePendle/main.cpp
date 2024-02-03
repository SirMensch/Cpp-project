#include <iostream>
#include <memory>
#include "Simulator.h"
#include "Stick.h"
#include "Platform.h"

int main() {
  // setup
  std::unique_ptr<Simulator> simulator = std::make_unique<Simulator>();

  Orientation orientation_stick = {400, 350, 0};
  Stick stick(5, 50, orientation_stick);
  Orientation orientation_platform = {350, 400, 0};
  Platform platform(100, 20, orientation_platform);

  simulator->addStick(stick);
  simulator->addPlatform(platform);


  // render loop
  bool finished = false;
  while (!finished) {
    finished = simulator->render();
  }

  // finish
  std::cout << "Render finished!" << std::endl;
  return 0;
}
