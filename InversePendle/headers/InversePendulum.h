//
// Created by larsl on 2/4/2024.
//

#ifndef INVERSEPENDLE__INVERSEPENDULUM_H_
#define INVERSEPENDLE__INVERSEPENDULUM_H_

#include <cmath>
#include <memory>
#include <iostream>
#include <list>

#include "Stick.h"
#include "Platform.h"
#if C_SLIDING_MODE
#include "SlidingMode.h"
#elif C_PID
#include "PID.h"
#elif
#include TODO
#endif

class InversePendulum {
 public:
  InversePendulum(float platform_width, float platform_height, float stick_width, float stick_height);
  std::list<std::shared_ptr<Object>> update(float delta_time, float force = 0.f);
 private:
  std::shared_ptr<Stick> stick_;
  std::shared_ptr<Platform> platform_;
  Differentials diff_theta_;
  Differentials diff_x_;
  Orientation platform_orientation_;
  Orientation stick_orientation_;
  std::shared_ptr<Controller> controller_;
};

#endif //INVERSEPENDLE__INVERSEPENDULUM_H_
