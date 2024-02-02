//
// Created by larsl on 1/22/2024.
//

#ifndef INVERSEPENDLE__OBJECT_H_
#define INVERSEPENDLE__OBJECT_H_

#include <memory>
#include "SFML/Graphics/RectangleShape.hpp"

class Object {
 public:
  // constructor
  Object(float width, float height); // both in cm
  virtual ~Object() = default;
  // functions
  virtual void updatePositon(float time_delta) = 0;
 private:
  // variables
  std::shared_ptr<sf::RectangleShape> rectangle;
  float weight;
};

#endif // INVERSEPENDLE__OBJECT_H_
