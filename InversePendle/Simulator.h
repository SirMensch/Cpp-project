//
// Created by larsl on 1/22/2024.
//
#ifndef INVERSEPENDLE__SIMULATOR_H_
#define INVERSEPENDLE__SIMULATOR_H_

#include <memory>
#include <list>

#include "SFML/Graphics.hpp"

#include "Object.h"


class Simulator {
 public:
  // constructor
  Simulator();
  // functions
  std::shared_ptr<sf::RenderWindow> get_window();
  bool render();
  bool addObject(Object& object);
 private:
  // variables
  std::list<std::shared_ptr<Object>> objects;
  std::shared_ptr<sf::RenderWindow> window;
};

#endif //INVERSEPENDLE__SIMULATOR_H_
