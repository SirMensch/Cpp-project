//
// Created by larsl on 2/2/2024.
//

#ifndef INVERSEPENDLE__STICK_H_
#define INVERSEPENDLE__STICK_H_

#include "Object.h"
#include <cmath>

class Stick : public Object {
 public:
  //Constructor
  Stick() = default;
  Stick(float width, float height, Orientation orientation);
  //function
  bool updatePosition(Orientation orientation) override;
 private:
};

#endif //INVERSEPENDLE__STICK_H_
