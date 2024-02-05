//
// Created by larsl on 1/22/2024.
//

#ifndef INVERSEPENDLE__OBJECT_H_
#define INVERSEPENDLE__OBJECT_H_

#define DENSITY 10 // kg/cm^2

#include <memory>
#include "SFML/Graphics/RectangleShape.hpp"
#include "structs.h"

class Object {
 public:
  // constructor
  Object() = default;
  Object(float width, float height, Orientation orientation); // both in cm
  virtual ~Object() = default;
  // functions
  std::shared_ptr<sf::RectangleShape> getRectangle();
  virtual bool updatePosition(Orientation orientation) = 0;
  [[nodiscard]] float getWeight() const;
  [[nodiscard]] float getHeight() const;
  [[nodiscard]] float getWidth() const;
 private:
  // variables
  std::shared_ptr<sf::RectangleShape> rectangle;
  float weight_ = 0;
};

#endif // INVERSEPENDLE__OBJECT_H_
