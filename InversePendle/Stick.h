//
// Created by larsl on 2/2/2024.
//

#ifndef INVERSEPENDLE__STICK_H_
#define INVERSEPENDLE__STICK_H_

#include "Object.h"

class Stick : public Object {
 public:
  //Constructor
  Stick(float width, float height, Orientation orientation);
  //function
  Orientation updatePosition(float time_delta) override;
 private:
};

#endif //INVERSEPENDLE__STICK_H_
