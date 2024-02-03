//
// Created by larsl on 2/3/2024.
//

#ifndef INVERSEPENDLE__PLATFORM_H_
#define INVERSEPENDLE__PLATFORM_H_

#include "Object.h"

class Platform : public Object{
 public:
  //Constructor
  Platform(float width, float height, Orientation orientation);
  //function
  Orientation updatePosition(float time_delta) override;
 private:
};

#endif //INVERSEPENDLE__PLATFORM_H_
