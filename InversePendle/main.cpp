#include <iostream>
#include <memory>
#include "Simulator.h"
#include "Object.h"


int main() {
  // setup
  std::unique_ptr<Simulator> simulator = std::make_unique<Simulator>();
  Object stick(5,100);
  Object platform(100,20);
  simulator->addObject(stick);
  simulator->addObject(platform);


  // render loop
  bool finished = false;
  while(!finished){
    finished = simulator->render();
  }

  // finish
  std::cout << "Render finished!" << std::endl;
  return 0;
}
