//
// Created by larsl on 2/2/2024.
//

#include "Stick.h"

bool Stick::updatePosition(Orientation orientation) {
  // TODO use boolean of this function & fix offset in connection
  try {
    Object::getRectangle()->setPosition(orientation.x, orientation.y - getWidth()/2 * std::sin(orientation.angle / 180.f * float(M_PI)));
    Object::getRectangle()->setRotation(orientation.angle);
  } catch (...) {
    return false;
  }
  return true;
}

Stick::Stick(float width, float height, Orientation orientation) : Object(width, height, orientation) {}
