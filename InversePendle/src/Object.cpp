//
// Created by larsl on 1/22/2024.
//

#include "Object.h"

Object::Object(float width, float height, Orientation orientation) {
  rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(CM_TO_M * width, CM_TO_M * height));
  weight_ = DENSITY * width * height;
  rectangle->setPosition(CM_TO_M * orientation.x,CM_TO_M * orientation.y);
  rectangle->setRotation(orientation.angle);
}
std::shared_ptr<sf::RectangleShape> Object::getRectangle() {
  return rectangle;
}
float Object::getWeight() const {
  return weight_;
}
float Object::getHeight() const {
  return rectangle->getSize().y / CM_TO_M;
}
float Object::getWidth() const {
  return rectangle->getSize().x / CM_TO_M;
}
