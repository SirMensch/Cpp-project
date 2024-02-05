//
// Created by larsl on 1/22/2024.
//

#include "Object.h"

Object::Object(float width, float height, Orientation orientation) {
  rectangle = std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height));
  weight_ = DENSITY * width * height;
  rectangle->setPosition(orientation.x, orientation.y);
  rectangle->setRotation(orientation.angle);
}
std::shared_ptr<sf::RectangleShape> Object::getRectangle() {
  return rectangle;
}
float Object::getWeight() const {
  return weight_;
}
float Object::getHeight() const {
  return rectangle->getSize().y;
}
float Object::getWidth() const {
  return rectangle->getSize().x;
}
