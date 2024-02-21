//
// Created by larsl on 2/2/2024.
//

#include "Stick.h"

bool Stick::updatePosition(Orientation orientation) {
  // TODO use boolean of this function
  try {
    float ori_x = orientation.x - getWidth() / 2 * std::cos(orientation.angle / 180.f * float(M_PI));
    float ori_y = orientation.y - getWidth() / 2 * std::sin(orientation.angle / 180.f * float(M_PI));
    Object::getRectangle()->setPosition(CM_TO_M * ori_x, CM_TO_M * ori_y);
    Object::getRectangle()->setRotation(orientation.angle);
  } catch (...) {
    return false;
  }
  return true;
}

Stick::Stick(float width, float height, Orientation orientation) : Object(width, height, orientation) {}
