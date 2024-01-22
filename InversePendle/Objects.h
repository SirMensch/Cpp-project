//
// Created by larsl on 1/22/2024.
//

#ifndef INVERSEPENDLE__OBJECTS_H_
#define INVERSEPENDLE__OBJECTS_H_

#include <memory>
#include "SFML/Graphics/RectangleShape.hpp"

class Objects {
  // constructor
  Objects(float width, float height){
    rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
  }
  // variables
  std::shared_ptr<sf::RectangleShape> rectangle;
  //
};

#endif // INVERSEPENDLE__OBJECTS_H_
