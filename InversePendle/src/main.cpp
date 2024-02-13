#include <iostream>
#include <memory>
#include "Simulator.h"
#include "InversePendulum.h"
#include "Config.h"


#define FRAMERATE 60

int main() {
  // setup
  // TODO remove config
  std::unordered_map<std::string, std::string> config = readConfig("config.txt");
  bool ext_force = (config["ExtForce"] == "true");

  std::unique_ptr<Simulator> simulator = std::make_unique<Simulator>(FRAMERATE);

  std::shared_ptr<InversePendulum> inverse_pendulum = std::make_shared<InversePendulum>(50, 20, 10, 100);

  simulator->addInversePendulum(*inverse_pendulum);

  // render loop
  bool finished = false;
  while (!finished) {
    finished = simulator->render();
  }

  // finish
  std::cout << "Render finished!" << std::endl;
  return 0;
}
