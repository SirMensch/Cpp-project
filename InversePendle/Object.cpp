//
// Created by larsl on 1/22/2024.
//

#include "Object.h"

#define DENSITY 0.2 // kg/cm^2

Object::Object(float width, float height, Orientation orientation) {
  rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
  weight = DENSITY * width * height;
  rectangle->setPosition(orientation.x, orientation.y);
  rectangle->setRotation(orientation.angle);
}
std::shared_ptr<sf::RectangleShape> Object::getRectangle() {
  return rectangle;
}
