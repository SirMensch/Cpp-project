//
// Created by larsl on 2/3/2024.
//

#include "Platform.h"
bool Platform::updatePosition(Orientation orientation) {
  // TODO check for the return value
  try {
    Object::getRectangle()->setPosition(orientation.x, orientation.y);
  } catch (...) {
    return false;
  }
  return true;
}
Platform::Platform(float width, float height, Orientation orientation) : Object(width, height, orientation) {
  Object::getRectangle()->setFillColor(sf::Color::Blue);
}
