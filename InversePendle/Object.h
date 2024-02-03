//
// Created by larsl on 1/22/2024.
//

#ifndef INVERSEPENDLE__OBJECT_H_
#define INVERSEPENDLE__OBJECT_H_

#include <memory>
#include "SFML/Graphics/RectangleShape.hpp"
#include "structs.h"

class Object {
 public:
  // constructor
  Object(float width, float height, Orientation orientation); // both in cm
  virtual ~Object() = default;
  // functions
  std::shared_ptr<sf::RectangleShape> getRectangle();
  virtual Orientation updatePosition(float time_delta) = 0;
 private:
  // variables
  std::shared_ptr<sf::RectangleShape> rectangle;
  float weight;
};

#endif // INVERSEPENDLE__OBJECT_H_
