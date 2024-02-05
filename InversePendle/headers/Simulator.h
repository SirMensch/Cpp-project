//
// Created by larsl on 1/22/2024.
//
#ifndef INVERSEPENDLE__SIMULATOR_H_
#define INVERSEPENDLE__SIMULATOR_H_

#include <memory>
#include <list>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "InversePendulum.h"

class Simulator {
 public:
  // constructor
  explicit Simulator(int framerate);
  // functions
  std::shared_ptr<sf::RenderWindow> get_window();
  bool render();
  void addInversePendulum(InversePendulum& inverse_pendulum);

 private:
  // variables
  std::shared_ptr<InversePendulum> inverse_pendulum_ = nullptr;
  std::shared_ptr<sf::RenderWindow> window_;
  int framerate_;
};

#endif //INVERSEPENDLE__SIMULATOR_H_
