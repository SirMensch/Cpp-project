//
// Created by larsl on 1/22/2024.
//
#ifndef INVERSEPENDLE__SIMULATOR_H_
#define INVERSEPENDLE__SIMULATOR_H_

#include <memory>
#include <list>

#include <SFML/Window.hpp>

#include "Objects.h"


class Simulator {
 public:
  // constructor
  Simulator(){
    window = std::make_shared<sf::Window>(sf::VideoMode(800, 600), "Inverse Pendulum");
  }
  // variables
  std::list<Objects> objects;
  // functions
  std::shared_ptr<sf::Window> get_window();
  bool render();
 private:
  std::shared_ptr<sf::Window> window;
};

#endif //INVERSEPENDLE__SIMULATOR_H_
