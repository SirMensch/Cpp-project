#include <iostream>
#include <memory>
#include <chrono>
#include "Simulator.h"
#include "InversePendulum.h"
#include "Config.h"

#define FRAMERATE 60

int main() {
  // TODO add boarders for simulation
  // setup

  std::unique_ptr<Simulator> simulator = std::make_unique<Simulator>(FRAMERATE);

  std::shared_ptr<InversePendulum> inverse_pendulum = std::make_shared<InversePendulum>(1.f, 0.2f, 0.1f, 1.f);
  simulator->addInversePendulum(*inverse_pendulum);

  // render loop
  bool finished = false;
  while (!finished) {
    auto startTime = std::chrono::high_resolution_clock::now();
    finished = simulator->render();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);
#if DEBUG
    std::cout << (duration.count() < (1 / 59.f)) << "\n";
#endif
  }

  // finish
  std::cout << "Render finished!" << std::endl;
  return 0;
}
