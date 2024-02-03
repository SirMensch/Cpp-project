//
// Created by larsl on 2/3/2024.
//

#include "Platform.h"
Orientation Platform::updatePosition(float time_delta) {
  // TODO euler method for the stick
  Orientation orientation;
  return orientation;
}
Platform::Platform(float width, float height, Orientation orientation) : Object(width, height, orientation) {}
