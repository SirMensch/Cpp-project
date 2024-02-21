//
// Created by larsl on 2/17/2024.
//

#ifndef INVERSEPENDLE_HEADERS_PID_H_
#define INVERSEPENDLE_HEADERS_PID_H_

#include "Controller.h"

class
PID : public Controller {
 public:
  PID(float k_proportional, float k_integral, float k_differential);
  float feedbackControl(Differentials diff_x, Differentials diff_theta, float delta_time) override;
 private:
  const float p_;
  const float i_;
  const float d_;
};

#endif //INVERSEPENDLE_HEADERS_PID_H_
